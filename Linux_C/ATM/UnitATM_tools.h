#ifndef UNITATM_TOOLS_H
#define UNITATM_TOOLS_H

#include <math.h>

typedef struct {
	int scale;		// skala - wykladnik 
	int resources[3];	// zasoby nominalow [5, 2, 1]
	int descriptor; // deskryptor na ktory maja byc wypisywane info o zetonach
	double delay;   // opoznienie w centysekundach
	unsigned int seed; 	// ziarno losowe
} Parameters;

void parse_arguments(int argc, char *argv[], Parameters *param);

// losujemy kolejnosc wydawania
void shuffle(int *tokens, int size);

// liczymy liczbe zetonow i reszte
int allocate_tokens(int value, int scale, int *resources, int *tokens);

// zmniejszanie zasobow po wydaniu
void decrease_resources(int *resources, const int *tokens);

void do_delay(double delay);


#endif

