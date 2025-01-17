#include <stdio.h>
#include <stdlib.h>
#define N 3

void powerset(int *val, int *disp, int r);

int main() {
    int val[N] = {1, 10, 25};
    int disp[N] = {10, 3, 2};
    int r = 27;

    powerset(val, disp, r);

    return 0;
}

static void powersetR(int pos, int r, int moneteUsate, int *moneteMin, int *val, int *disp, int *sol, int *bestSol){
    if(r == 0){
        // controllo se la soluzione corrente (sol) è migliore
        if(moneteUsate < *moneteMin){
            *(moneteMin) = moneteUsate;
            for (int i = 0; i < N; ++i) {
                bestSol[i] = sol[i];
            }
        }
        return;
    }

    if(r < 0 || pos >= N) return;

    for (int i = 0; i <= disp[pos]; i++) {
        sol[pos] = i;  // Usiamo `i` monete del tipo corrente
        powersetR(pos+1, r - (i * val[pos]), moneteUsate + i, moneteMin, val, disp, sol, bestSol);
    }

    // backtrack sulla monete corrente, ripristino il numero delle monete usate
    sol[pos] = 0;
}

void powerset(int *val, int *disp, int r){
    int pos = 0;
    int moneteUsate = 0;
    int moneteMin = 10000;

    int *sol = calloc(N, sizeof (int));
    int *bestSol = calloc(N, sizeof (int));

    powersetR(pos, r, moneteUsate, &moneteMin, val, disp, sol, bestSol);

    if(moneteMin == 10000){
        printf("No resto!");
    }

    printf("Numero di monete usate minimo %d\n", moneteMin);
    for (int i = 0; i < N; i++) {
        if(bestSol[i] != 0){
            printf("%d monete da %d", bestSol[i], val[i]);
            printf("\n");
        }
    }
    free(sol);
    free(bestSol);
}