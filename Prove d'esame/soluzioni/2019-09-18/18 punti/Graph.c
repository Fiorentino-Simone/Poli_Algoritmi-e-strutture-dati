#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"

struct graph{
    int V;
    int E;
    int **matradj;
    ST tab;

    int nr, nc;
};

Graph GRAPHinit(int nV){
    Graph G = malloc(sizeof(*G));
    G->V = nV;
    G->E = 0;
    G->matradj = malloc(sizeof(int *) * nV);
    for (int i = 0; i < G->V; i++) {
        G->matradj[i] = malloc(sizeof (int) * nV);
    }
    G->tab = STinit(nV);
    return G;
}

Graph GRAPHload(){
    Graph G;
    FILE *fin;

    fin = fopen("mappa.txt", "r");
    if(fin == NULL){
        printf("Errore nell'apertura del file!");
        exit(-1);
    }

    fscanf(fin, "%d %d", &nr, &nc)

    G = GRAPHinit();

    return G;
}