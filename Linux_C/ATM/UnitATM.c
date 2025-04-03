#include "UnitATM_tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <ctype.h>

void process_requests(Parameters *param) {
	char line[256];
	while (fgets(line, sizeof(line), stdin)) {
		
		char *p = line;
    while (isspace((unsigned char)*p)) p++;
    if (*p == '\0') {
      continue;
    }
		char *end;
	  int value = strtol(line, &end, 10);

		if (*end != '\0' && *end != '\n') {
		 	fprintf(stderr, "Nieprawidłowy wiersz: %s", line);
      continue;
    }

    if (value < 0) {
      fprintf(stderr, "Liczba musi być nieujemna: %s", line);
      continue;
    }

		// mznozymy przez skale
    value *= param->scale;
		// liczymy ilosc zetonow i reszte
    int tokens[3] = {0, 0, 0};
    int remainder = allocate_tokens(value, param->scale, param->resources, tokens);
	
    // RESZTA
    if (remainder > 0) {
      printf("reszta: %d\n", remainder);
    }

		int total = tokens[0] + tokens[1] + tokens[2];
    int *all_tokens = malloc(total * sizeof(int));

    if (!all_tokens) {
      fprintf(stderr, "Blad alokacji pamięci\n");
       exit(EXIT_FAILURE);
    }

		int idx = 0;
    int denominations[3] = {5, 2, 1};
    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < tokens[i]; j++) {
        all_tokens[idx++] = denominations[i] * param->scale; // wartosc zetonu
      }
    }
		shuffle(all_tokens, total);
        	
		// ZETONY DO DESKRYPTORA
    FILE *output = fdopen(param->descriptor, "w");
    if (!output) {
      perror("fdopen");
      free(all_tokens);
      exit(EXIT_FAILURE);
    }
		for (int i = 0; i < total; i++) {
      fprintf(output, "%d\n", all_tokens[i]);
      fflush(output);
      do_delay(param->delay);
    }
    fprintf(output, "\n");
    fflush(output);
		free(all_tokens);
  }
}

int main(int argc, char *argv[]) {
  Parameters param = {1, {0, 0, 0}, 1, 1.0};
  parse_arguments(argc, argv, &param);

  process_requests(&param);
  return 0;
}

