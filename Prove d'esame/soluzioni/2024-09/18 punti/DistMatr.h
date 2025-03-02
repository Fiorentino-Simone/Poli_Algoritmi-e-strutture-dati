#ifndef INC_18_PUNTI_DISTMATR_H
#define INC_18_PUNTI_DISTMATR_H

#include <stdlib.h>

typedef struct matrDist *distMatr;


distMatr DISTMATRinit(int N);
distMatr DISTMATRread(int N, FILE *fin);
void DISTMATRprint(distMatr matr);

int * MATRgetrow(distMatr matr, int i);
int MATRgetN(distMatr matr);
int MATRgetvalue(distMatr matr, int i, int j);

#endif //INC_18_PUNTI_DISTMATR_H
