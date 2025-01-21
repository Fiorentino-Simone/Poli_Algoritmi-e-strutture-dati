#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

#define MAXL 20

int main() {
    char descrG[MAXL];
    char elencoVertexF[MAXL];
    char foutName[MAXL];

    int nV = 0;
    int cnt = 0;
    int *sol;

    /*printf("Inserisci il nome del file dove prendere la descrizione del Grafo:  ");
    scanf("%s", descrG);
    printf("Inserisci il nome del file dove prendere l'elenco archo:  ");
    scanf("%s", elencoVertexF);
    printf("Inserisci il nome del file per la stampa:  ");
    scanf("%s", foutName);*/

    FILE *fin = fopen("graph.txt", "r");
    if(fin == NULL){
        printf("Errore nell'apertura del file!");
        exit(-1);
    }

    Graph G = GRAPHload(fin);

    // prendo in input i vertici e verifico se possono essere kernel di G
    fin = fopen("vertex.txt", "r");
    if(fin == NULL){
        printf("Errore nell'apertura del file!");
        exit(-1);
    }
    sol = kernelRead(fin, G, &cnt);
    if(isKernel(G, sol, cnt)){
        printf("I vertici inseriti sono kernel di G\n");
    } else {
        printf("I vertici inseriti NON sono kernel di G\n");
    }

    printf("L'insieme K minimo del Kernel di G vale: ");
    GRAPHKernelMin(G);

    fclose(fin);
    GRAPHfree(G);
    return 0;
}

