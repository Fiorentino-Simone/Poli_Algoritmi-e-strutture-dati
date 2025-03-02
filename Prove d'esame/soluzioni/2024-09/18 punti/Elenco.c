#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "Elenco.h"

struct elencoCitta{
    char **nomi;
    int nCitta;
};

elenco ELENCOinit(int N){
    elenco el;
    el = malloc(sizeof(*el));

    el->nCitta = N;
    el->nomi = malloc(sizeof(char *) * N);
    for (int i = 0; i < N; i++) {
        el->nomi[i] = malloc(sizeof(char) * MAXL);
    }

    return el;
}

elenco caricaDati(distMatr *Matr){
    FILE *fin;
    int N;
    elenco e;

    fin = fopen("distanze.txt", "r");
    if(fin == NULL){
        printf("Errore nell'apertura del file!");
        exit(-1);
    }

    fscanf(fin, "%d", &N);
    e = ELENCOinit(N);
    for (int i = 0; i < N; i++) {
        fscanf(fin, "%s", e->nomi[i]);
    }

    (*Matr) = DISTMATRread(N, fin);

    return e;
}

void ELENCOprinti(elenco el){
    for (int i = 0; i < el->nCitta; i++) {
        printf(" %s ", el->nomi[i]);
    }
    printf("\n");
}

static elenco ELENCOsenzaAmbulatorio(elenco el, SEDI sol){
    elenco elNew;
    int k = 0;
    elNew = malloc(sizeof(*el));
    elNew->nCitta = el->nCitta - SEDIgetN(sol);
    for (int i = 0; i < el->nCitta; i++) {
        if(SEDIsearchCitta(sol, el->nomi[i]) == -1){
            strcpy(elNew->nomi[k++], el->nomi[i]);
        }
    }
    return elNew;
}

static int checkIfAmbulatorio(elenco elNew, elenco el, int j){
    for (int i = 0; i < elNew->nCitta; i++) {
        if(strcmp(elNew->nomi[i], el->nomi[j]) == 0){
            return -1;
        }
    }
    return 1;
}

static int checkIfAmbulatorioPossible(elenco elNew, elenco el, int i, distMatr matr, int MAXD, SEDI sol){
    int *row = MATRgetrow(matr, i);
    int hasAmbulatorio;
    for (int j = 0; j < MATRgetN(matr); j++) {
        if(MATRgetvalue(matr, i, j) <= MAXD){
            hasAmbulatorio = checkIfAmbulatorio(elNew, el, j);
            if(hasAmbulatorio == -1){
                continue;
            } else {
                if (checkIfServirla(sol, el->nomi[j])){
                    return 1;
                } else continue;
            }
        }
    }
    return 0;
}

int checkSedi(distMatr matr, int MAXD, SEDI sol, elenco el){
    // funzione che restituisce 0 se la soluzioni sedi non è accettabile, 1 viceversa
    elenco elencoCittaNew;

    // per ogni citta, escluse le M citta in SEDI, ho bisogno che esista almeno una sede di pronto soccorso (tra le M) a
    // distanza <= MAXD
    elencoCittaNew = ELENCOsenzaAmbulatorio(el, sol);
    for (int i = 0; i < elencoCittaNew->nCitta; i++) {
        if (!(checkIfAmbulatorioPossible(elencoCittaNew, el, i, matr, MAXD, sol))){
            // passata la row della matrice che corrisponde ad una citta SENZA ambulatorio,
            // controllo che nella riga ci sia almeno un valore <= MAXD, se esiste quel valore (j-colonna)
            // bisogno controllare che in quella citta sia l'ambulatorio --> scorro tutte le elencoCittaNew e controllo che sia
            // presente el->citta[j] se è presente NON HA AMBULATORIO senno
            // controllare che l'ambulatorio posso servirla (checkIfServirla) senno vai avanti
            return 0;
        }
    }

    return 1;
}