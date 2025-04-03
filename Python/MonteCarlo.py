import math
import random
import numpy as np
import matplotlib.pyplot as plt

# Funkcja losuje punkty w zakresie [0,1], 
# następnie sprawdzane jest czy punkt ten znjaduje się wewnątrz okręgu
# Estymowanie wartosci pi opiera się na zależności między polem ćwiartki koła a polem kwadratu
# Stosunek tych pól wynosi: (1/4 pi r^2) / r^2  =   pi / 4
# Z tego wynika, że PI = 4 * LICZBA_PKT_W_KOLE / LICCZBA_WSZYSTKICH_PKT
def MonteCarlo(N): # przyjmuje ilość punktów
    # Współrzędne wylosowanych pkt
    X = []
    Y = []
    # liczba punktów wewnątrz koła
    inside = 0

    for i in range(N):
        x = random.uniform(0, 1)
        y = random.uniform(0, 1)
        X.append(x)
        Y.append(y)

        # rownanie okregu o srodku w pkt (0,0):  x^2 + y^2 = 1
        if x**2 + y**2 <= 1 :
            inside += 1     # punkt jest w okregu

    PI = 4*(inside / N)     # 4* pkt w kole / wszyskie pkt
    return PI, X, Y


# wizualizacja losowania punktów
N = [100, 1000, 10000, 100000] # ilosc próbek

# Widzimy, że punkty wewnątrz ćwiartki koła są niebieskie, a punkty poza nią czerwone
fig, ax = plt.subplots(2,2, figsize=(10,10))
for i in range(4):
    n = N[i]
    PI, X, Y = MonteCarlo(n)

    alpha = np.linspace(0, np.pi / 2, 1000)  # od 0 do 90 stopni
    x_circle = np.cos(alpha)  # wsp okręgu
    y_circle = np.sin(alpha)

    # index osie ax[i//2, i%2]
    ax[i//2, i%2].plot(x_circle, y_circle, color='blue')

    # pkt wewnątrz okręgu - niebieskie
    ax[i//2, i%2].scatter([x for x, y in zip(X, Y) if x**2 + y**2 <= 1],
                          [y for x, y in zip(X, Y) if x**2 + y**2 <= 1],
                          color='blue', s=1)

    # pkt na zewnątrz okręgu - czerwone
    ax[i//2, i%2].scatter([x for x, y in zip(X, Y) if x**2 + y**2 > 1],
                          [y for x, y in zip(X, Y) if x**2 + y**2 > 1],
                          color='red', s=1)

    ax[i//2, i%2].set_xlim(0, 1)
    ax[i//2, i%2].set_ylim(0, 1)
    ax[i//2, i%2].grid(True)
    ax[i//2, i%2].set_aspect('equal')
    ax[i//2, i%2].set_title(f'N = {n}')


# Kumulatywna estymacja 
# Przy każdym losowaniu uśredniamy wartość o wynik z poprzednich iteracji,
# dzięki czemu mamy mniejsze odchylenia od rzeczywistej wartości
# Im iększa ilość punktów, tym bardziej stabilna jest estymacja
values = range(1, 500) 
# Dla zakresu 500 widać, że wartość pod koniec losowań jest ustabilizowana
estimated_pi = []
prev_pi = 0

for value in values:
    current_pi, _, _ = MonteCarlo(value)
    prev_pi = (prev_pi * (value - 1) + current_pi) / value # ulepszamy estymację średnią z innych prób
    estimated_pi.append(prev_pi)

fig, ax = plt.subplots(figsize=(10, 10))
ax.plot(values, estimated_pi)
ax.axhline(y=math.pi, color='red', linestyle='--')
ax.set_title('Zbieżność estymacji')
ax.set_xlabel('Liczba losowan')
ax.set_ylabel('Estymacja pi')
ax.set_ylim(2, 4)

# Boxplot przedstawia rozkład estymacji liczby pi dla różnej leiczby punktów
# Dla każdej ilości N powtarzamy estymację 10 razy, zeby sprawdzic jak zmienia się estymacja
# Dla małej ilości próbek wartości są rozproszone, dla większych wartość się stabilizuje
res = {n: [] for n in N}

for n in N:
    for _ in range(10): # powtarzamy 10 razy
        pi_estimate, _, _ = MonteCarlo(n)
        res[n].append(pi_estimate)

plt.figure(figsize=(10, 6))
plt.boxplot(res.values(), labels=[str(n) for n in N])
plt.axhline(y=np.pi, color='blue', linestyle='--', linewidth=1)
plt.title('Rozkład estymacji pi dla różnej liczby punktów')
plt.xlabel('Liczba punktów (N)')
plt.ylabel('Estymowana wartość pi')
plt.show()


# Wnioski
# Metoda Monte Carlo jest skuteczna w estymowaniu liczby pi, jednak nie jest bardzo dokładna.
# W miarę zwiększania liczby losowań estymowana wartość zbliża się do rzeczywistej wartości pi
# - czyli, im więcej mamy wylosowanych punktów, tym dokładniejsza będzie estymacja.
# Jednak, aby uzyskać bardziej precyzyjny wynik, potrzebna jest bardzo duża liczba losowań, 
# co może wpływać na czas wykonywania obliczeń
