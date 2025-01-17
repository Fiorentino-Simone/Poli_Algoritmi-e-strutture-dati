#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define R 7 // numero di stringhe
#define C 8 // numero massimo di lettere

void powerset(char S[R][C]);

int main() {

    char S[R][C] = {
        "ABGCIEF",
        "BA",
        "CD",
        "FE",
        "GHBD",
        "JKLGHI",
        "FK"
    };

    powerset(S);

    return 0;
}

static int checkSolution(int *sol, char S[R][C], int k){
    for (int i = 0; i < k; i++) {
        for (int j = i+1; j < k; j++) {
            for (int p = 0; p < strlen(S[sol[i]]); p++) {
                for (int l = 0; l < strlen(S[sol[j]]); l++) {
                    if(S[sol[i]][p] == S[sol[j]][l]) return 0;
                }
            }
        }
    }
    return 1;
}

static void comb_sempl(int pos, int start, int k, char S[R][C], int *sol, int *stop){
    if(*(stop) == 1) return;

    if(pos >= k){
        if(checkSolution(sol, S, k)){
            *(stop) = 1;
            for(int i = 0; i < k; i++){
                printf("%s ", S[sol[i]]);
            }
            printf("\n");
        }
        return;
    }

    for (int i = start; i < R; i++) {
        sol[pos] = i;
        comb_sempl(pos+1, i+1, k, S, sol, stop);
    }
}

void powerset(char S[R][C]){
    int pos = 0;
    int start = 0;
    int stop = 0;
    int k;

    int *sol = calloc(R, sizeof(int));

    for (k = R; k >= 1 && stop == 0; k--) {
        comb_sempl(pos, start, k, S, sol, &stop);
    }
    printf("Il numero massimo di stringhe mutualmente disgiunte vale: %d", (k+1));
    free(sol);
}

