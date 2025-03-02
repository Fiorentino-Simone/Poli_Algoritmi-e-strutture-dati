#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "SEDI.h"

struct sediProntoSoccorso{
    char **citta;
    int *servito; // vettore contatore che viene decrementato ogni volta che scegli una citta
    int M;
};

int SEDIgetN(SEDI sol){
    return sol->M;
}

char *SEDIgetCitta(SEDI sol, int i){
    return sol->citta[i];
}

int SEDIsearchCitta(SEDI sol, char *citta){
    for (int i = 0; i < sol->M; i++) {
        if(strcmp(sol->citta[i], citta) == 0){
            return i;
        }
    }
    return -1;
}

int checkIfServirla(SEDI sol, char *citta){
    int index = SEDIsearchCitta(sol, citta);
    if(sol->servito[index] > 0){
        sol->servito[index]--;
        return 1;
    } else {
        return 0;
    }
}