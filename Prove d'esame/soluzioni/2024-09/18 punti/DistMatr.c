#include <stdio.h>
#include <stdlib.h>

#include "DistMatr.h"

struct matrDist{
    int **matr;
    int NR, NC;
};

distMatr DISTMATRinit(int N){
    distMatr matr;
    matr = malloc(sizeof(*matr));

    matr->NC = matr->NR = N;
    matr->matr = malloc(sizeof(int *) * N);
    for (int i = 0; i < N; i++) {
        matr->matr[i] = malloc(sizeof(int) * N);
    }

    return matr;
}

distMatr DISTMATRread(int N, FILE *fin){
    distMatr matr = DISTMATRinit(N);

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            fscanf(fin, "%d", &matr->matr[i][j]);
        }
    }

    return matr;
}

void DISTMATRprint(distMatr matr){
    printf("\n");
    for (int i = 0; i < matr->NR; i++) {
        for (int j = 0; j < matr->NC; j++) {
            printf(" %d ", matr->matr[i][j]);
        }
        printf("\n");
    }
}

int * MATRgetrow(distMatr matr, int i){
    int *row = malloc(sizeof(int) * matr->NR);
    for (int j = 0; j < matr->NC; j++) {
        row[i] = matr->matr[i][j];
    }
    return row;
}

int MATRgetN(distMatr matr){
    return matr->NC;
}

int MATRgetvalue(distMatr matr, int i, int j){
    return matr->matr[i][j];
}