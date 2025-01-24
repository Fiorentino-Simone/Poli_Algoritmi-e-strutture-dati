#include "Item.h"

typedef struct edge
{
    int v;
    int w;
    int wt; // se il grafo è pesato
} Edge;

typedef struct graph *Graph;


Graph GRAPHinit(int V);
void GRAPHfree(Graph G);

Graph GRAPHload(FILE *fin);
void GRAPHstore(Graph G, FILE *fout);

int GRAPHgetIndex(Graph G, char *label); // ritorna l'indice della tabella di hash passata la label chiave univoca

void GRAPHinsertE(Graph G, int id1, int id2; int wt); // wt solo se il grafo è pesato
void GRAPHremoveE(Graph G, int id1, int id2);

void GRAPHedges(Graph G, Edge *a); // funzione che serve per la memorizzazione degli archi in un array

int GRAPHpath(Graph G, int id1, int id2); // Cammino semplice tra due vertici
void GRAPHpathH(Graph G, int id1, int id2); // Cammino di Hamilton solo per grafi non orientati

void GRAPHbfs(Graph G, int id); // visita in ampiezza
void GRAPHdfs(Graph G, int id); // visita in profondità

int GRAPHcc(Graph G); // componenti connesse (non orientato)

int GRAPHscc(Graph G); // componenti fortemente connesse (orientato)
Graph GRAPHreverse(Graph G);