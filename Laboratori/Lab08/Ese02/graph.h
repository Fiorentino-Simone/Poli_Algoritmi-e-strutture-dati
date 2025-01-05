#ifndef ESE02_GRAPH_H
#define ESE02_GRAPH_H

#include <stdio.h>
#include "st.h"

#define MAXL 30

typedef struct edge {
    int v, w, wt;
} Edge;

// ADT di prima classe
typedef struct graph *Graph;

// PROTOTIPI
// creatore e distruttore
Graph GRAPHinit(int V);
void GRAPHfree(Graph G);

// carica da file e inserimento
Graph GRAPHload(FILE *fin);
Graph GRAPHloadL(Graph G, FILE *fin);
void GRAPHinsertE(Graph G, int id1, int id2, int wt);

int GRAPHgetIndex(Graph G, char *label1, char *label2);

// stampa
void GRAPHstore(Graph G, FILE *fout);
void GRAPHstoreOrd(Graph G, FILE *fout);


void GRAPHedges(Graph G, Edge *a);
void GRAPHverificaAdiacenza(Graph G, int rappr);
Graph GRAPHloadLFromM(Graph G, FILE *fin);

#endif //ESE02_GRAPH_H
