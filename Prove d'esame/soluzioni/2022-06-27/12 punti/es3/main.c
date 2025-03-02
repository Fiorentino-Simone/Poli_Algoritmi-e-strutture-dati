#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define N 26

void wrapper(char lettere[2*N], int k, int p);

int main() {

    char lettere[2*N] = {
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j',
        'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't',
        'u', 'v', 'w', 'x', 'y', 'z', 'A', 'B', 'C', 'D',
        'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N',
        'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X',
        'Y', 'Z'
    };

    int k, p;
    printf("inserisci la lunghezze delle sequenze: ");
    scanf("%d", &k);

    printf("\n");
    printf("inserisci il numero di volte che si possono ripetere i caratteri: ");
    scanf("%d", &p);

    wrapper(lettere, k, p);

    return 0;
}

static int check(char *sol, int k){
    int cnt = 0;
    for (int i = 0; i < k; i++) {
        if(!isupper(sol[i])){
            cnt++;
        }
    }
    return cnt > (k/2) ? 0 : 1;
}

static void disp_rip(char *sol, int *mark, char lettere[2*N], int k, int pos){
    if(pos >= k){
        if(check(sol, k)){
            printf("Sequenza: ");
            for (int i = 0; i < k; i++) {
                printf(" %c ", sol[i]);
            }
            printf("\n");
        }
        return;
    }

    for (int i = 0; i < (2*N); i++) {
        if(mark[i] > 0){
            mark[i]--;
            sol[pos] = lettere[i];
            disp_rip(sol, mark, lettere, k, pos+1);
            mark[i]++;
        }
    }
}

void wrapper(char lettere[2*N], int k, int p){
    char *sol;
    int *mark;
    int pos = 0;
    sol = calloc(k, sizeof(char));

    //disposizioni con ripetizioni
    mark = calloc(2*N, sizeof(int));
    for (int i = 0; i < 2*N; i++) {
        mark[i] = p;
    }

    disp_rip(sol, mark, lettere, k, pos);

    free(sol);
    free(mark);
}
