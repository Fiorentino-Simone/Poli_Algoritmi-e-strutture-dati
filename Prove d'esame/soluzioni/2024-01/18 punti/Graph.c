#include <stdlib.h>
#include <stdio.h>

#include "Graph.h"

struct graph {
    int nV, nE;
    int **matradj;
    Vertice *vertici;
};

GRAPH GRAPHinit(int nV){
    GRAPH G = malloc(sizeof(*G));
    G->nV = nV;
    G->nE = 0;
    G->matradj = calloc(nV, sizeof(int *));
    for (int i = 0; i < nV; i++) {
        G->matradj[i] = calloc(nV, sizeof (int));
    }
    G->vertici = malloc(nV * sizeof(Vertice));
    return G;
}

static Edge EdgeCreate(int id1, int id2){
    Edge e;
    e.v = id1;
    e.w = id2;
    return e;
}

static void insertE(GRAPH G, Edge e){
    int v = e.v;
    int w = e.w;

    if(G->matradj[v][w] == 0){
        G->nE++;
    }
    G->matradj[v][w] = 1;
}

void GRAPHinsertE(GRAPH G, int id1, int id2){
    insertE(G, EdgeCreate(id1, id2));
}

GRAPH GRAPHload(){
    FILE *fin;
    int nV, nE, id1, id2;
    
    fin = fopen("graph.txt", "r");
    fscanf(fin, "%d %d", &nV, &nE);

    GRAPH G = GRAPHinit(nV);
    for (int i = 0; i < nV; i++) {
        fscanf(fin, "%d %s %d", &id1, G->vertici[i].name, &G->vertici[i].val);
    }

    for (int i = 0; i < nE; i++) {
        fscanf(fin, "%d %d", &id1, &id2);
        GRAPHinsertE(G, id1, id2);
    }

    fclose(fin);
    return G;
}

void GRAPHprint(GRAPH G){
    printf("Stampa dei vertici: \n");
    for (int i = 0; i < G->nV; ++i) {
        printf("%d %s %d\n", i, G->vertici[i].name, G->vertici[i].val);
    }
    printf("Stampa degli archi: \n");
    for (int i = 0; i < G->nV; i++) {
        for (int j = 0; j < G->nV; j++) {
            printf(" %d ", G->matradj[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void GRAPHfree(GRAPH G){
    for (int i = 0; i < G->nV; ++i) {
        free(G->matradj[i]);
    }
    free(G->matradj);
    free(G->vertici);
    free(G);
}

void checkString(GRAPH G, char *stringa){

}