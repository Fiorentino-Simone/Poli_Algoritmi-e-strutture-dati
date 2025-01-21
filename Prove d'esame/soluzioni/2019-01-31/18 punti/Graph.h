#ifndef INC_18_PUNTI_GRAPH_H
#define INC_18_PUNTI_GRAPH_H

#include "ST.h"

typedef struct{
    int v;
    int w;
} Edge;

typedef struct grafo *Graph;

Graph GRAPHinit(int nV);
void GRAPHfree(Graph G);

Graph GRAPHload(FILE *fin);
void GRAPHinsertE(Graph G, int id1, int id2);

void GRAPHprintmatrix(Graph G);

int *kernelRead(FILE *fin, Graph G, int *cnt);
int isKernel(Graph G, int *sol, int cnt);

void GRAPHKernelMin(Graph G);
void GRAPHminimumKernel(FILE *out, Graph G);

#endif //INC_18_PUNTI_GRAPH_H
