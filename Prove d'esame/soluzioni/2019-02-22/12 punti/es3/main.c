#include <stdio.h>
#include <stdlib.h>

#define N 9

void powerset(int *V);
void combinazioni_semp(int pos, int start, int k, int *V, int *sol, int *stop);

int main() {
    int V[N] = {8, 9, 6, 4, 5, 7, 3, 2, 4};

    powerset(V);

    return 0;
}

static int checkSolution(int *Y, int k){
    int error = 0;
    for (int i = 0; i < k-1; i++) {
        if(i % 2 == 0){
            if (Y[i] >= Y[i + 1]){
                error = 1;
            }
        }
        else{
            if(Y[i] <= Y[i+1]){
                error = 1;
            }
        }

        if(error == 1){
            return 1;
        }
    }
    return error;
}

void combinazioni_semp(int pos, int start, int k, int *V, int *sol, int *stop){
    if(*(stop) == 0) return;

    if(pos >= k){
        if(checkSolution(sol, k) == 0){
            *(stop) = 0;
            for (int i = 0; i < k; i++) {
                printf("%d ", sol[i]);
            }
        }
        return;
    }

    for (int i = start; i < N; i++) {
        sol[pos] = V[i];
        combinazioni_semp(pos+1, i+1, k, V, sol, stop);
    }
}

void powerset(int *V){
    int pos = 0;
    int start = 0;
    int stop = 1;

    int *sol = calloc(N, sizeof(int));

    for (int k = N; k >= 1 && stop == 1; k--) {
        combinazioni_semp(pos, start, k, V, sol, &stop);
    }

    free(sol);
}