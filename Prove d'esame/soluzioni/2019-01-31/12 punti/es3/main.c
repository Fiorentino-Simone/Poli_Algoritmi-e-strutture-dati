#include <stdio.h>
#include <stdlib.h>

#define N 4
#define M 4

void maxValore(int *lunghezze, int *prezzo);

int main() {
    int lunghezze[M] = {4,1,3,2};
    int prezzo[M] = {9,1,8,5};

    maxValore(lunghezze, prezzo);

    return 0;
}

static void algoritmoEr(int pos, int currentBlocchi, int *sol, int *bestSol, int *lunghezze, int *prezzo, int *maxValue, int *blocchiMax){
    int i,j;
    int lunghezza_singolo;
    int currentPrice;

    /* currentBlocchi va a suddivedere i blocchi a 0 a N */

    if (pos >= N){
        currentPrice = 0;
        for (i = 0; i < currentBlocchi; i++) {
            lunghezza_singolo = 0;
            for (j = 0; j < N; j++) {
                if(sol[j] == i){
                    lunghezza_singolo++;
                }
            }

            currentPrice += prezzo[lunghezza_singolo-1]; // funziona solo perchè è ordinato
            if(currentPrice > *maxValue){
                *maxValue = currentPrice;
                *blocchiMax = currentBlocchi;
                for (i = 0; i < N; i++) {
                    bestSol[i] = sol[i];
                }
            }
        }
        printf("\n");
        return;
    }

    for (i = 0; i < currentBlocchi; i++) {
        sol[pos] = i;
        algoritmoEr(pos+1, currentBlocchi, sol, bestSol, lunghezze, prezzo, maxValue, blocchiMax);
    }
    sol[pos] = currentBlocchi;
    algoritmoEr(pos+1, currentBlocchi+1, sol, bestSol, lunghezze, prezzo, maxValue, blocchiMax);
}

static void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}

static void sort(int *lunghezza, int *prezzo) {
    int i, j;
    for (i = 0; i < M - 1; i++) {
        for (j = 0; j < M - i - 1; j++) {
            if (lunghezza[j] > lunghezza[j + 1]) {
                swap(&lunghezza[j], &lunghezza[j + 1]);
                swap(&prezzo[j], &prezzo[j + 1]);
            }
        }
    }
}

void maxValore(int *lunghezze, int *prezzo){
    int *bestSol, *sol;
    int maxValue = 0;
    int blocchiMax = 0;

    bestSol = malloc(sizeof (int)* N);
    sol = malloc(sizeof (int)* N);

    //ho ordinato lunghezze e creato corrispondenza indice-lunghezza-prezzo
    sort(lunghezze, prezzo);

    algoritmoEr(0, 0, sol, bestSol, lunghezze, prezzo, &maxValue, &blocchiMax);

    for (int i = 0; i < blocchiMax; i++) {
        printf("{");
        for(int j = 0; j < N; j++){
            /*
             * Dentro bestSol mi ritrovo valori da 0 a blocchi-1
             * stampo per blocchi la scelta
             */
            if(bestSol[j] == i) {
                printf("-");
            }
        }
        printf("}");
    }
    printf("\n");
    printf("Valore massimo complessivo: %d", maxValue);

    free(bestSol);
    free(sol);
}



