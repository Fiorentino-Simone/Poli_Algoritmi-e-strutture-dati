#include <stdio.h>
#include <stdlib.h>

#define N 4

void wrapper(int M[N][N]);
void algoritmoER(int pos, int *stop, int m, int *sol, int M[N][N]);

int main(){
    int M[N][N] = {
            {1,1,0,1},
            {1,1,0,1},
            {0,0,1,0},
            {1,1,0,1}
    };

    /*
     * suddividere le persone nel minor numero di gruppi
     * possibili facendo in modo che tutte le persone in un gruppo siano mutualmente amiche
     */

    wrapper(M);

    return 0;
}

void wrapper(int M[N][N]){
    // uso l'algoritmo di ER
    int *sol = malloc(sizeof(int) * N);
    int pos, stop, m;

    pos = stop = m = 0;

    algoritmoER(pos, &stop, m, sol, M);

    free(sol);
}

static int check(int *sol, int M[N][N], int m){
    for (int k = 0; k < m; k++) {
        for (int i = 0; i < N; i++) {
            if(sol[i] == k){
                for (int j = i+1; j < N; j++) {
                    if(sol[j] == k){
                        if(M[i][j] == 0){
                            return 0;
                        }
                    }
                }
            }
        }
    }
    return 1;
}

void algoritmoER(int pos, int *stop, int m, int *sol, int M[N][N]){
    if(*stop == 1){
        return;
    }

    if(pos >= N){
        if(check(sol, M, m)){
            (*stop) = 1;
            //stampa delle partizioni
            for (int i = 0; i < m; i++) {
                printf("{");
                for (int j = 0; j < N; j++) {
                    if(sol[j] == i){
                        printf(" %d ", j);
                    }
                }
                printf("}");
                printf("\n");
            }
        }
        return;
    }

    for (int i = 0; i < m; i++) {
        sol[pos] = i;
        algoritmoER(pos+1, stop, m, sol, M);
    }
    sol[pos] = m;
    algoritmoER(pos+1, stop, m+1, sol, M);
}


