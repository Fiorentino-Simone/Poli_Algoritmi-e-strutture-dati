#ifndef ESE01_GRAPH_H
#define ESE01_GRAPH_H

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

// stampa
void GRAPHstore(Graph G, FILE *fout);

// DAG
void GRAPHfindBackEdges(Graph G, int id, Edge *backEdges);
void DAGcreate(Graph G, Edge *backEdges);
void DAGpathMax(Graph G);

// inserisci e rimuovi
void GRAPHinsertE(Graph G, int id1, int id2, int wt);
void GRAPHremoveE(Graph G, int id1, int id2);

void GRAPHedges(Graph G, Edge *a);
int GRAPHcount(Graph G);

#endif //ESE01_GRAPH_H
