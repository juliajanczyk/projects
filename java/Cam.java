import java.nio.ByteBuffer;
import java.io.File;
import javafx.application.Application;
import javafx.scene.Scene;
import javafx.scene.image.WritableImage;
import javafx.scene.image.PixelFormat;
import javafx.scene.canvas.Canvas;
import javafx.scene.canvas.GraphicsContext;
import javafx.scene.paint.Color;

import javafx.scene.layout.BorderPane;
import javafx.scene.layout.VBox;
import javafx.scene.layout.HBox;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.stage.Stage;
import javafx.animation.KeyFrame;
import javafx.animation.Timeline;
import javafx.event.ActionEvent;
import javafx.util.Duration;
import javafx.stage.FileChooser;
import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.nio.IntBuffer;

import cam.Frames;



public class Cam extends Application {
    private static final int FRAME_WIDTH = 640;
    private static final int FRAME_HEIGHT = 480;
    private static Slider zoomSlider = new Slider(1.0, 5.0, 1.0);
    private static Label zoomLabel = new Label("Zoom (1x)");

    GraphicsContext gc;
    Canvas canvas;
    byte buffer[];

    Frames frames;

    double brightness = 1.0;
    double zoom = 1.0;
    double contrast = 1.0;
    double offsetX = 0;
    double offsetY = 0;

    public static void main(String[] args) {
        launch(args);
    }

    @Override
    public void start(Stage primaryStage) {
        int result;
        Timeline timeline;

        frames = new Frames();
        result = frames.open_shm("/frames");
        primaryStage.setTitle("MIKROSKOP");
        BorderPane root = new BorderPane();
        root.setStyle("-fx-background-color: #7fffd4;"); // jasny zielony: #ccffcc

        canvas = new Canvas(FRAME_WIDTH, FRAME_HEIGHT);
        gc = canvas.getGraphicsContext2D();

        // Panel boczny z guzikami
        VBox sidePanel = new VBox(20);
        sidePanel.setStyle("-fx-padding: 20;");

        // Guziki jasności
        Label brightnessLabel = new Label("Jasność:");
        Button brightnessMinus = new Button("-");
        Button brightnessPlus = new Button("+");
        brightnessMinus.setMinSize(60, 40); // Większe przyciski
        brightnessPlus.setMinSize(60, 40);
        brightnessMinus.setOnAction(e -> adjustBrightness(-0.1));
        brightnessPlus.setOnAction(e -> adjustBrightness(0.1));
        HBox brightnessControls = new HBox(10, brightnessMinus, brightnessPlus);

        // Guziki kontrastu
        Label contrastLabel = new Label("Kontrast:");
        Button contrastMinus = new Button("-");
        Button contrastPlus = new Button("+");
        contrastMinus.setMinSize(60, 40);
        contrastPlus.setMinSize(60, 40);
        contrastMinus.setOnAction(e -> adjustContrast(-0.1));
        contrastPlus.setOnAction(e -> adjustContrast(0.1));
        HBox contrastControls = new HBox(10, contrastMinus, contrastPlus);

        // Guzik zapisu obrazu
        Button saveButton = new Button("Zapis obrazu");
        saveButton.setMinSize(120, 50); // Większy przycisk
        saveButton.setOnAction(e -> snap(primaryStage));

        // Guzik reset
        Button resetButton = new Button("Reset");
        resetButton.setMinSize(120, 50); // Większy przycisk
        resetButton.setOnAction(e -> resetSettings());

        // Wskaźnik powiększenia
        //Label zoomLabel = new Label("Zoom (1x)");

        // Suwak powiększenia
        //Slider zoomSlider = new Slider(1.0, 5.0, 1.0);
        zoomSlider.setPrefWidth(400);
        zoomSlider.setShowTickLabels(true);
        zoomSlider.valueProperty().addListener((obs, oldVal, newVal) -> {
            zoom = newVal.doubleValue();
            zoomLabel.setText("Zoom (" + String.format("%.1fx", zoom) + ")");
            drawFrame();
        });

        // Panel boczny
        sidePanel.getChildren().addAll(
            brightnessLabel, brightnessControls,
            contrastLabel, contrastControls,
            saveButton, resetButton,
            zoomLabel
        );

        // Panel dolny dla suwaka
        HBox bottomPanel = new HBox(20, new Label("Suwak do przybliżania i oddalania:"), zoomSlider);
        bottomPanel.setStyle("-fx-padding: 20; -fx-alignment: center;");

        // Strzałki przesuwania
        Button upButton = new Button("↑");
        upButton.setMinSize(40, 40);
        upButton.setOnAction(e -> {
            offsetY += 20;
            drawFrame();
        });
        Button downButton = new Button("↓");
        downButton.setMinSize(40, 40);
        downButton.setOnAction(e -> {
            offsetY -= 20;
            drawFrame();
        });
        Button leftButton = new Button("←");
        leftButton.setMinSize(40, 40);
        leftButton.setOnAction(e -> {
            offsetX += 20;
            drawFrame();
        });
        Button rightButton = new Button("→");
        rightButton.setMinSize(40, 40);
        rightButton.setOnAction(e -> {
            offsetX -= 20;
            drawFrame();
        });

        VBox arrowControls = new VBox(10, upButton, new HBox(10, leftButton, rightButton), downButton);
        arrowControls.setStyle("-fx-padding: 20; -fx-alignment: center;");

        // Układ
        root.setCenter(canvas);
        root.setRight(sidePanel);   // Przyciski po prawej
        root.setBottom(bottomPanel); // Suwak na dole
        root.setLeft(arrowControls); // Strzałki nawigacyjne po lewej? czy zmieniamy na prawo?

        timeline = new Timeline(new KeyFrame(Duration.millis(130), e -> disp_frame()));
        timeline.setCycleCount(Timeline.INDEFINITE);
        timeline.play();

        Scene scene = new Scene(root, 1200, 700);
        primaryStage.setScene(scene);
        primaryStage.show();
    }

    private void adjustBrightness(double delta) {
        brightness = Math.max(0.5, Math.min(2.0, brightness + delta));
        drawFrame();
    }

    private void adjustContrast(double delta) {
        contrast = Math.max(0.5, Math.min(2.0, contrast + delta));
        drawFrame();
    }

    private void resetSettings() {
        brightness = 1.0;
        contrast = 1.0;
        zoom = 1.0;

        offsetX = 0;
        offsetY = 0;

        zoomSlider.setValue(1.0);
        zoomLabel.setText("Zoom (1x)");

        drawFrame();
    }

    private void disp_frame() {

        buffer = frames.get_frame();

        if (buffer == null || buffer.length != FRAME_WIDTH * FRAME_HEIGHT * 3) {
            System.err.println("Nieprawidłowe dane obrazu!");
            return;
        }

        WritableImage image = new WritableImage(FRAME_WIDTH, FRAME_HEIGHT);
        IntBuffer pixelBuffer = IntBuffer.allocate(FRAME_WIDTH * FRAME_HEIGHT);

        for (int i = 0; i < buffer.length; i += 3) {
            int r = (int) ((buffer[i] & 0xFF) * brightness);
            int g = (int) ((buffer[i + 1] & 0xFF) * brightness);
            int b = (int) ((buffer[i + 2] & 0xFF) * brightness);

            r = Math.min(255, Math.max(0, r));
            g = Math.min(255, Math.max(0, g));
            b = Math.min(255, Math.max(0, b));

            int color = (0xFF << 24) | (r << 16) | (g << 8) | b;
            pixelBuffer.put(color);
        }
        pixelBuffer.rewind();
        image.getPixelWriter().setPixels(0, 0, FRAME_WIDTH, FRAME_HEIGHT, PixelFormat.getIntArgbInstance(), pixelBuffer, FRAME_WIDTH);
        gc.clearRect(0, 0, canvas.getWidth(), canvas.getHeight());
        gc.drawImage(image, offsetX, offsetY, FRAME_WIDTH * zoom, FRAME_HEIGHT * zoom);
    }

    private void drawFrame() {
        gc.clearRect(0, 0, FRAME_WIDTH, FRAME_HEIGHT);
        gc.fillText("Obraz z mikroskopu", FRAME_WIDTH / 2 - 50, FRAME_HEIGHT / 2);
    }

    private void snap(Stage primaryStage) {
        WritableImage writableImage = canvas.snapshot(null, null);
        FileChooser fileChooser = new FileChooser();
        fileChooser.setTitle("Zapisz");
        fileChooser.getExtensionFilters().add(new FileChooser.ExtensionFilter("Pliki PNG", "*.png"));
        File file = fileChooser.showSaveDialog(primaryStage);

         if (file != null) {
            try {
                BufferedImage bufferedImage = new BufferedImage((int) writableImage.getWidth(), (int) writableImage.getHeight(), BufferedImage.TYPE_INT_ARGB);
                IntBuffer intBuffer = IntBuffer.allocate((int) (writableImage.getWidth() * writableImage.getHeight()));
                writableImage.getPixelReader().getPixels(0, 0, (int) writableImage.getWidth(), (int) writableImage.getHeight(), PixelFormat.getIntArgbInstance(), intBuffer, (int) writableImage.getWidth());
                intBuffer.rewind();

                for (int y = 0; y < (int) writableImage.getHeight(); y++) {
                    for (int x = 0; x < (int) writableImage.getWidth(); x++) {
                        bufferedImage.setRGB(x, y, intBuffer.get());
                    }
                }

                ImageIO.write(bufferedImage, "png", file);
                System.out.println("Zapisano zrzut ekranu: " + file.getAbsolutePath());
            } catch (Exception e) {
                System.err.println("Blad podczas zapisu zrzutu ekranu: " + e.getMessage());
            }
        }
    }
}
