#ifndef INC_18_PUNTI_GRAPH_H
#define INC_18_PUNTI_GRAPH_H

typedef struct {
    int v;
    int w;
} Edge;

typedef struct {
  int u;
  int v;
  int w;
} triangle;

typedef struct graph *Graph;

Graph GRAPHload();

Graph GRAPHinit(int nV);
void GRAPHfree(Graph G);

void GRAPHinsertE(Graph G, int id1, int id2);

int GRAPHverifica(Graph G, char *filename);
void GRAPHsolve(Graph G);

void GRAPHstore(Graph G, FILE *fout);

#endif //INC_18_PUNTI_GRAPH_H
