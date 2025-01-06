#include <stdlib.h>
#include "graph.h"

// DICHIARAZIONE per la lista
typedef struct node *link;
struct node
{
    int v, wt;
    link next;
};

// DICHIARAZIONE dell'ADT di prima classe
struct graph
{
    int V;
    int E;
    int **madj;
    link *ladj;
    ST tab;
    link z;
};

/* region: TOOLS per la matrice */
static int **MATRIXint(int r, int c, int val)
{
    int **t;

    t = malloc(r * sizeof(int *));
    for (int i = 0; i < r; i++)
    {
        t[i] = malloc(c * sizeof(int));
    }

    for (int i = 0; i < r; i++)
    {
        for (int j = 0; j < c; j++)
        {
            t[i][j] = val;
        }
    }
    return t;
}

static Edge EDGEcreate(int v, int w, int wt)
{
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}
/* endregion */

/* region: LISTA */
link NEW(int v, int wt, link next)
{
    link x = malloc(sizeof(*x));
    x->v = v;
    x->wt = wt;
    x->next = next;
    return x;
}
/* endregion */

Graph GRAPHinit(int V)
{
    Graph G;
    G = malloc(sizeof *G);
    G->V = V;
    G->E = 0;

    // inizializzo la matrice delle adiacenze
    G->madj = MATRIXint(V, V, 0);
    // inizializzo la lista delle adiacenze
    G->z = NEW(-1, -1, NULL);
    G->ladj = malloc(G->V * sizeof(link));
    for (int i = 0; i < G->V; i++)
    {
        G->ladj[i] = G->z;
    }
    // inizializzo la tabella di simboli
    G->tab = STinit(V);

    return G;
}

void GRAPHfree(Graph G)
{
    link j, next;

    // distruzione della matrice delle adiacenze
    for (int i = 0; i < G->V; i++)
    {
        free(G->madj[i]);
    }
    free(G->madj);

    // distruzione della lista delle adiacenze
    for (int i = 0; i < G->V; i++)
    {
        for (j = G->ladj[i]; j != G->z; j = next)
        {
            next = j->next;
            free(j);
        }
    }

    free(G->ladj);
    free(G->z);
    STfree(G->tab);
    free(G);
}

Graph GRAPHload(FILE *fin)
{
    Graph G;
    int E, flusso;
    char elab1[MAXL], rete1[MAXL], elab2[MAXL], rete2[MAXL];
    E = 1;
    flusso = 0;

    // leggere fino alla fine del file per capire quante righe ci sono
    while (!feof(fin))
    {
        char c = fgetc(fin);
        if (c == '\n')
        {
            E++;
        }
    }
    rewind(fin); // riavvolge il file

    G = GRAPHinit(2 * E); // inizializzo il grafo sovrastimando il numero di vertici
    for (int i = 0; i < E; i++)
    {
        fscanf(fin, "%s %s %s %s %d\n", elab1, rete1, elab2, rete2, &flusso);
        GRAPHinsertE(G, GRAPHgetIndex(G, elab1, rete1), GRAPHgetIndex(G, elab2, rete2), flusso);
    }
    return G;
}

Graph GRAPHloadL(Graph G, FILE *fin)
{
    // inserire i dati nella lista delle adiacenze dal file
    rewind(fin);
    int flusso;
    char elab1[MAXL], rete1[MAXL], elab2[MAXL], rete2[MAXL];
    for (int i = 0; i < G->E; i++)
    {
        fscanf(fin, "%s %s %s %s %d\n", elab1, rete1, elab2, rete2, &flusso);
        G->ladj[GRAPHgetIndex(G, elab1, rete1)] = NEW(GRAPHgetIndex(G, elab2, rete2), flusso, G->ladj[GRAPHgetIndex(G, elab1, rete1)]);
        G->ladj[GRAPHgetIndex(G, elab2, rete2)] = NEW(GRAPHgetIndex(G, elab1, rete1), flusso, G->ladj[GRAPHgetIndex(G, elab2, rete2)]);
    }
    return G;
}

static void insertE(Graph G, Edge e)
{
    int v, w, wt;
    v = e.v;
    w = e.w;
    wt = e.wt;

    if (G->madj[v][w] == 0)
    {
        G->E++; // salvo l'effettivo numero degli archi
    }

    // Grafo non orientato e pesato
    G->madj[v][w] = wt;
    G->madj[w][v] = wt;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt)
{
    insertE(G, EDGEcreate(id1, id2, wt));
}

int GRAPHgetIndex(Graph G, char *name, char *subnet)
{
    int id;
    id = STsearch(G->tab, name);
    if (id == -1)
    {
        id = STcount(G->tab);
        STinsert(G->tab, name, subnet);
    }
    return id;
}

void GRAPHedges(Graph G, Edge *a)
{
    int E = 0;

    for (int v = 0; v < G->V; v++)
    {
        for (int w = v + 1; w < G->V; w++)
        {
            if (G->madj[v][w] != 0)
            {
                a[E++] = EDGEcreate(v, w, G->madj[v][w]);
            }
        }
    }
}

void GRAPHstore(Graph G, FILE *fout)
{
    Edge *a;

    a = malloc(G->E * sizeof(Edge));
    if (a == NULL)
    {
        return;
    }

    fprintf(fout, "Numero di archi: %d\n", G->E);
    fprintf(fout, "Stampa con matrice delle adiacenze\n");
    GRAPHedges(G, a);

    for (int i = 0; i < G->E; i++)
    {
        fprintf(fout, "%s %s %s %s %d\n", STsearchByIndexName(G->tab, a[i].v), STsearchByIndexSubnet(G->tab, a[i].v), STsearchByIndexName(G->tab, a[i].w), STsearchByIndexSubnet(G->tab, a[i].w), a[i].wt);
    }

    fprintf(fout, "\n \n \n");

    if (G->ladj[0] != G->z){
        a = malloc(G->E * sizeof(Edge));
        if (a == NULL)
        {
            return;
        }
        printf("Stampa con lista delle adiacenze\n");
        for (int i = 0; i < G->V; i++)
        {
            for (link j = G->ladj[i]; j != G->z; j = j->next)
            {
                if (i < j->v)
                {
                    a[i] = EDGEcreate(i, j->v, j->wt);
                    fprintf(fout, "%s %s %s %s %d\n", STsearchByIndexName(G->tab, a[i].v), STsearchByIndexSubnet(G->tab, a[i].v), STsearchByIndexName(G->tab, a[i].w), STsearchByIndexSubnet(G->tab, a[i].w), a[i].wt);
                }
            }
        }
    }

    free(a);
}

void GRAPHstoreOrd(Graph G, FILE *fout)
{
    int n = STcount(G->tab);
    int *a = malloc(n * sizeof(int));
    STsort(G->tab, a);
    for (int i = 0; i < n; i++)
    {
        fprintf(fout, "VERTICE: %s\n", STsearchByIndexName(G->tab, a[i]));
        for (int j = 0; j < n; j++)
        {
            if (i != j && G->madj[a[i]][a[j]] != 0)
            {
                fprintf(fout, "ARCHI: %s\n", STsearchByIndexName(G->tab, a[j]));
            }
        }
    }
    free(a);
}

static int isSubGraphComplete(Graph G, int id1, int id2, int id3)
{
    if (G->madj[id1][id2] != 0 && G->madj[id1][id3] != 0 && G->madj[id2][id3] != 0)
    {
        return 1;
    }
    return 0;
}

static int isAdjacent(link *adjList, int id1, int id2)
{
    link current = adjList[id1];
    while (current != NULL)
    {
        if (current->v == id2)
        {
            return 1;
        }
        current = current->next;
    }
    return 0;
}

static int isSubGraphCompleteL(Graph G, int id1, int id2, int id3)
{
    // Controlla se ogni coppia di vertici è adiacente
    if (isAdjacent(G->ladj, id1, id2) &&
        isAdjacent(G->ladj, id1, id3) &&
        isAdjacent(G->ladj, id2, id1) &&
        isAdjacent(G->ladj, id2, id3) &&
        isAdjacent(G->ladj, id3, id1) &&
        isAdjacent(G->ladj, id3, id2))
    {
        return 1;
    }
    return 0;
}

void GRAPHverificaAdiacenza(Graph G, int rappr)
{
    /* dati 3 vertici letti da tastiera, verificare se essi sono adiacenti a coppie (sottografo completo)*/
    char v1[MAXL], v2[MAXL], v3[MAXL];
    int id1, id2, id3;

    // Esempio funzionante: "Shiva", "Yrden", "Cassiel"
    printf("Inserisci il primo vertice: ");
    scanf("%s", v1);
    printf("Inserisci il secondo vertice: ");
    scanf("%s", v2);
    printf("Inserisci il terzo vertice: ");
    scanf("%s", v3);

    id1 = STsearch(G->tab, v1);
    id2 = STsearch(G->tab, v2);
    id3 = STsearch(G->tab, v3);

    if (id1 == -1 || id2 == -1 || id3 == -1)
    {
        printf("Errore: uno o piu' vertici non esistono nella tabella dei simboli.\n");
        return;
    }

    if (rappr == 0)
    {
        // rappresentazione con matrice
        if (isSubGraphComplete(G, id1, id2, id3))
        {
            printf("I vertici sono adiacenti a coppie\n");
        }
        else
        {
            printf("I vertici non sono adiacenti a coppie\n");
        }
    }
    else
    {
        // rappresentazione con lista
        if (isSubGraphCompleteL(G, id1, id2, id3))
        {
            printf("I vertici sono adiacenti a coppie\n");
        }
        else
        {
            printf("I vertici non sono adiacenti a coppie\n");
        }
    }
}

Graph GRAPHloadLFromM(Graph G)
{
    // trasformare la matrice delle adiacenze in lista delle adiacenze
    for (int i = 0; i < G->V; i++)
    {
        for (int j = i + 1; j < G->V; j++)
        {
            if (G->madj[i][j] != 0)
            {
                G->ladj[i] = NEW(j, G->madj[i][j], G->ladj[i]);
                G->ladj[j] = NEW(i, G->madj[i][j], G->ladj[j]);
            }
        }
    }
    return G;
}
