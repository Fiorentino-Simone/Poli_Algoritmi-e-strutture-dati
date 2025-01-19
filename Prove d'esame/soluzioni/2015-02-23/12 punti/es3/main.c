#include <stdio.h>
#include <stdlib.h>

#define N_LETTERE 26
#define N_CIFRE 10

void perm_rip(char *lettere, int *cifre, int pos, int maxlen, int *sol, int *mark_lettere, int *mark_cifre);
void powerset(char *lettere, int *cifre, int k);

int main() {
    char lettere[N_LETTERE] = {'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};
    int cifre[N_CIFRE] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};

    int k = 2;

    powerset(lettere, cifre, k);

    return 0;
}

void perm_rip(char *lettere, int *cifre, int pos, int maxlen, int *sol, int *mark_lettere, int *mark_cifre){
    if(pos >= maxlen){
        printf("\n");
        for (int i = 0; i < maxlen; i++) {
            if(i <= 2){
                printf("%c ", lettere[sol[i]]);
            } else {
                printf("%d ", cifre[sol[i]]);
            }
        }
        return;
    }

    if(pos <= 2 && pos >= 0){
        // usiamo le prime 3 celle per generare delle lettere
        for (int i = 0; i < N_LETTERE; i++) {
            if(mark_lettere[i] > 0){
                mark_lettere[i]--;
                sol[pos] = i;
                perm_rip(lettere, cifre, pos+1, maxlen, sol, mark_lettere, mark_cifre);
                mark_lettere[i]++;
            }
        }
    }
    else if(pos <=4 && pos > 2){
        // le ultime 2 celle per generare le cifre
        for (int i = 0; i < N_CIFRE; i++) {
            if(mark_cifre[i] > 0){
                mark_cifre[i]--;
                sol[pos] = i;
                perm_rip(lettere, cifre, pos+1, maxlen, sol, mark_lettere, mark_cifre);
                mark_cifre[i]++;
            }
        }
    }
}

void powerset(char *lettere, int *cifre, int k){
    //MODELLO calcolo combinatorio: permutazioni con ripetizione
    int pos = 0;
    int maxlen = 5;

    int *mark_lettere = calloc(N_LETTERE, sizeof (int));
    int *mark_cifre = calloc(N_CIFRE, sizeof (int));

    int *sol = calloc(maxlen, sizeof (int));

    for (int i = 0; i < N_LETTERE; i++) {
        mark_lettere[i] = k;
    }
    for (int i = 0; i < N_CIFRE; i++) {
        mark_cifre[i] = k;
    }

    perm_rip(lettere, cifre, pos, maxlen, sol, mark_lettere, mark_cifre);

    free(mark_cifre);
    free(mark_lettere);
    free(sol);
}