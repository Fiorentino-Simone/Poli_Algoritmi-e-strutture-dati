#ifndef INC_18_PUNTI_GRAPH_H
#define INC_18_PUNTI_GRAPH_H

#include "ST.h"

typedef struct {
    int v;
    int w;
} Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int nV);
void GRAPHfree(Graph G);

Graph GRAPHload();


#endif //INC_18_PUNTI_GRAPH_H
