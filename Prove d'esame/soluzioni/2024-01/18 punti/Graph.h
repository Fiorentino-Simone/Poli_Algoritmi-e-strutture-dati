#ifndef INC_18_PUNTI_GRAPH_H
#define INC_18_PUNTI_GRAPH_H

#define MAXL 20

typedef struct {
    int v;
    int w;
} Edge;

typedef struct {
    char name[MAXL];
    int val;
} Vertice;

typedef struct graph *GRAPH;

GRAPH GRAPHinit(int nV);
void GRAPHfree(GRAPH G);

GRAPH GRAPHload();

void GRAPHinsertE(GRAPH G, int id1, int id2);

void GRAPHprint(GRAPH G);

void checkString(GRAPH G, char *stringa);



#endif //INC_18_PUNTI_GRAPH_H
