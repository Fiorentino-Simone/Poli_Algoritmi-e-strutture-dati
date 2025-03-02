#include <stdlib.h>
#include <stdio.h>

#define N 5

void stampaMatr(int **matr);

int main() {
    int **matr;

    matr = malloc(sizeof(int *) * N);
    for (int i = 0; i < N; i++) {
        matr[i] = malloc(sizeof(int) * N);
    }

    // uso proprietà della matrice simmetrica
    // triangolo superiore
    int k = 0;
    for (int i = 0; i < N; i++) {
        for (int j = i; j < N; j++) {
            matr[i][j] = k;
            k++;
        }
        k = 0;
    }

    // triangolo inferiore
    for (int i = 0; i < N; i++) {
        k = i;
        for (int j = 0; j < i+1; j++) {
            matr[i][j] = k;
            k--;
        }
    }

    stampaMatr(matr);

    for (int i = 0; i < N; i++) {
        free(matr[i]);
    }
    free(matr);
    return 0;
}

void stampaMatr(int **matr){
    for (int i = 0; i < N; i++) {
        printf("\n");
        for (int j = 0; j < N; j++) {
            printf(" %d ", matr[i][j]);
        }
        printf("\n");
    }
}