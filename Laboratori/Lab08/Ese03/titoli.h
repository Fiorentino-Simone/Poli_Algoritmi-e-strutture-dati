#ifndef ESE01_TITOLI_H
#define ESE01_TITOLI_H

#define MAXC 21

#include "quotazioni.h"

typedef struct titolo *Titolo;
typedef struct listTitolo *LISTtitolo; // ADT di 1^classe lista ordinata

// PROTOTIPI:
// creazione e distruzione
LISTtitolo LISTinit();
void LISTfree(LISTtitolo l);

// lettura da file
LISTtitolo readfile(FILE *fp, LISTtitolo l);

// stampa
void LISTprint(LISTtitolo l);

// ricerca
void searchTitle(LISTtitolo l);
void searchQuotation(LISTtitolo l);
void searchQuotationMinMax(LISTtitolo l);
void searchQuotationMinMaxAllPeriod(LISTtitolo l);

// bilanciamento
void balanceTree(LISTtitolo l);

#endif // ESE01_TITOLI_H
