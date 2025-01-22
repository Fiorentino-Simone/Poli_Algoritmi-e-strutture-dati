#ifndef INC_18_PUNTI_DIVISIONE_H
#define INC_18_PUNTI_DIVISIONE_H

#include "dipendente.h"

#define N 4

typedef struct {
    int m;
    int cmin;
    int r;
} Statistiche;

typedef struct divisione_t *Divisione;

// PROTOTIPI
Divisione DIVISIONEinit();
void DIVISIONEfree(Divisione d);

Divisione DIVISIONEacquisizione(FILE *fin);
void DIVISIONEprint(Divisione d);

void DIVISIONEaddDipendente(Divisione div, Dipendente dip);

#endif //INC_18_PUNTI_DIVISIONE_H
