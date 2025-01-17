#include <stdio.h>
#include <stdlib.h>

#define N 9

void powerset(int *V);

int main(){
    int V[N] = {4, 2, 5, 9, 7, 6, 10, 3, 1};

    powerset(V);

    return 0;
}

static int checksolution(int *sol, int k){
    int crescente = 1;
    int decrescente = 0;

    for(int i = 0; i < k-1; i++){
        if(sol[i] == sol[i+1]) return 0;

        if(sol[i] > sol[i+1] && crescente == 1){
            decrescente = 1;
            crescente = 0;
        }

        if(sol[i] < sol[i+1] && decrescente == 1){
            crescente = -1;
            decrescente = -1;
        }
    }

    if(crescente == 1 && decrescente==0) return 1;
    if(crescente == 0 && decrescente==1) return 1;
    return 0;
}

static void powerset_combsempl(int pos, int start, int *sol, int *V, int *stop, int k){
    int i;

    if((*stop)==1) return;

    if(pos >= k){
        //check
        if(checksolution(sol, k)){
            (*stop) = 1;
            printf("Sequenza bitonica di lunghezza massima %d\n", k);
            for(i = 0; i < k; i++){
                printf("%d ",sol[i]);
            }
        }
        return;
    }

    for(i = start; i < N; i++){
        sol[pos] = V[i];
        powerset_combsempl(pos+1, i+1, sol, V, stop, k);
    }
}

void powerset(int *V){
    int pos=0;
    int start=0;
    int stop=0;

    int *sol = (int *) malloc(N*sizeof(int));

    for(int k = N; k >= 1 && stop == 0; k--){
        powerset_combsempl(pos, start, sol, V, &stop, k);
    }
    free(sol);
}
