#ifndef INC_18_PUNTI_ELENCO_H
#define INC_18_PUNTI_ELENCO_H

#include "DistMatr.h"
#include "SEDI.h"

#define MAXL 25

typedef struct elencoCitta *elenco;

elenco ELENCOinit(int N);

elenco caricaDati(distMatr *Matr);
void ELENCOprinti(elenco el);

int checkSedi(distMatr matr, int MAXD, SEDI sol, elenco el);

#endif //INC_18_PUNTI_ELENCO_H