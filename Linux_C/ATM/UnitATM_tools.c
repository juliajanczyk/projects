#include "UnitATM_tools.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <time.h>
#include <math.h>
#include <errno.h>

void parse_arguments(int argc, char* argv[], Parameters* param) {
  param->seed = (unsigned int)getpid(); // domyslnie PID
  int opt;
  char* endptr;

  while ((opt = getopt(argc, argv, "u:m:t:s:d:")) != -1)
  {
    switch (opt)
    {
    case 'u':
      errno = 0;
      long exp = strtol(optarg, &endptr, 10);
      if (errno != 0 || *endptr != '\0' || exp < 0)
      {
        fprintf(stderr, "Skala ma byc nieujemna.\n");
        exit(EXIT_FAILURE);
      }
      param->scale = 1; // gdy wartosc -u to 0 to scale = 1
      for (int i = 0; i < exp; i++)
      {
        param->scale *= 10;
      }
    case 'm': {
      char* token = strtok(optarg, ":");
      for (int i = 0; i < 3 && token; i++)
      {
        errno = 0;
        long value = strtol(token, &endptr, 10);
        if (errno != 0 || *endptr != '\0' || value < 0)
        {
          fprintf(stderr, "Wartosci -m maja byc >= 0\n");
          exit(EXIT_FAILURE);
        }
        param->resources[i] = (int)value;
        token = strtok(NULL, ":");
      }
      break;
    }
    case 't':
      errno = 0;
      long descriptor = strtol(optarg, &endptr, 10);
      if (errno != 0 || *endptr != '\0' || descriptor <= 0)
      {
        fprintf(stderr, "Nieprawidlowy deskryptor. Powinien byc wiekszy od 0\n");
        exit(EXIT_FAILURE);
      }
      param->descriptor = (int)descriptor;
      break;

    case 's':
      errno = 0;
      long s = strtol(optarg, &endptr, 10);
      if (errno != 0 || *endptr != '\0' || s < 0)
      {
        fprintf(stderr, "Ziarno powinno byc liczba calkowita nieujemna\n");
        exit(EXIT_FAILURE);
      }
      param->seed = (unsigned int)s;
      break;
    case 'd':
      errno = 0;
      double d = strtod(optarg, &endptr);
      if (errno != 0 || *endptr != '\0' || d <= 0)
      {
        fprintf(stderr, "Opoznienie musi byc wieksze od 0\n");
        exit(EXIT_FAILURE);
      }
      param->delay = d * 0.01; // Konwertujemy centysekundy na sekundy
      break;
    default:
      fprintf(stderr, "Uzycie: %s -u <skala> -m <zasoby> -t <deskryptor> [-s <ziarno>] [-d <opoznienie>]\n", argv[0]);
      exit(EXIT_FAILURE);

    }

  }

  // sprawdzamy czy -m podane
  if (param->resources[0] == 0 && param->resources[1] == 0 && param->resources[2] == 0)
  {
    fprintf(stderr, "Brak argumentu -m lub niewlasciwe wartosci\n");
    exit(EXIT_FAILURE);
  }
  srandom(param->seed);
}

void shuffle(int* tokens, int size) {
  for (int i = size - 1; i > 0; i--)
  {
    int j = random() % (i + 1);
    int temp = tokens[i];
    tokens[i] = tokens[j];
    tokens[j] = temp;
  }
}

int allocate_tokens(int value, int scale, int* resources, int* tokens) {
  int denominations[3] = { 5, 2, 1 };
  int remainder = value;

  for (int i = 0; i < 3; i++)
  {
    int denom_value = denominations[i] * scale;
    tokens[i] = remainder / denom_value;
    if (tokens[i] > resources[i])
    {
      tokens[i] = resources[i];
    }
    remainder -= tokens[i] * denom_value;
  }

  decrease_resources(resources, tokens);

  return remainder;
}

void decrease_resources(int* resources, const int* tokens) {
  for (int i = 0; i < 3; i++)
  {
    resources[i] -= tokens[i];
  }
}

void do_delay(double delay) {
  long nano_w_sec = 1000000000;
  struct timespec ts;
  ts.tv_sec = (time_t)delay;              // czesc calkowita sekund
  ts.tv_nsec = (long)((delay - ts.tv_sec) * nano_w_sec); // czesc nanosekundowa
  nanosleep(&ts, NULL);
}

