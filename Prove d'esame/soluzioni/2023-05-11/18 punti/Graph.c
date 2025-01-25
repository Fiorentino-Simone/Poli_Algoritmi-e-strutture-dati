#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

typedef struct node *link;

struct node {
    int val;
    link next;
};

struct graph{
    int V;
    int E;
    link *ladj;
    link z;
};

static link NEWnode(int val, link next){
    link node = malloc(sizeof(*node));
    node->val = val;
    node->next = next;
    return node;
}

Graph GRAPHinit(int nV){
    Graph G = malloc(sizeof(*G));
    G->V = nV;
    G->E = 0;
    G->z = NEWnode(-1, NULL);
    G->ladj = malloc(sizeof(link) * nV);
    for (int v = 0; v < G->V; v++) {
        G->ladj[v] = G-> z;
    }
    return G;
}


Graph GRAPHload(){
    Graph G;
    int nV;
    FILE *fin;
    int id1, id2;

    fin = fopen("grafo.txt", "r");
    if(fin == NULL){
        printf("Errore nell'apertura del file!");
        exit(-1);
    }

    fscanf(fin, "%d", &nV);

    G = GRAPHinit(nV);
    while(fscanf(fin, "%d %d", &id1, &id2) == 2){
        if(id1 != -1 && id1 < nV && id2 < nV && id2 != -1){
            GRAPHinsertE(G, id1, id2);
        }
    }

    fclose(fin);
    return G;
}

static Edge EDGEcreate(int id1, int id2){
    Edge e;
    e.v = id1;
    e.w = id2;
    return e;
}

static void insertE(Graph G, Edge e){
    int v = e.v, w = e.w;
    G->ladj[v] = NEWnode(w, G->ladj[v]);
    G->ladj[w] = NEWnode(v, G->ladj[w]);
    G->E++;
}

void GRAPHinsertE(Graph G, int id1, int id2){
    insertE(G, EDGEcreate(id1, id2));
}

void GRAPHedges(Graph G, Edge *a)
{
    int v, E = 0;
    for (v = 0; v < G->V; v++)
    {
        for (link t = G->ladj[v]; t != G->z; t = t->next)
        {
            if(v < t->val){
                a[E++] = EDGEcreate(v, t->val);
            }
        }
    }
}

void GRAPHstore(Graph G, FILE *fout)
{
    int i;
    Edge *a;
    a = malloc(G->E * sizeof(Edge));
    GRAPHedges(G, a); // dipende dalla rappresentazione
    fprintf(fout, "%d\n", G->V);
    for (i = 0; i < G->V; i++)
        fprintf(fout, "%d\n", i);
    for (i = 0; i < G->E; i++)
        fprintf(fout, "%d  %d\n", a[i].v, a[i].w);

    free(a);
}

int GRAPHverifica(Graph G, char *filename){
    FILE *fin;
    int k, uscita = 0, cnt = 0;
    triangle *triangles;
    Edge *a = malloc(G->E * sizeof (Edge)); // GRANDE QUANTO G->E
    int *visited = calloc(G->V, sizeof(int));

    fin = fopen(filename, "r");
    if(fin == NULL){
        printf("Errore nella lettura del file!");
        exit(-1);
    }

    // deve verificare che sia un triangle packing
    // ho il file strutturato come una lista di sottoinsiemi,
    // ognuno da 3 vertici ciascuno

    // CONTROLLI da fare:
    // 1) nel sottoinsieme letto i vertici siano diversi (ui diverso da vi diverso da wi)
    // 2) esistano gli archi (ui, wi), (ui, vi), (wi, vi)
    // 2) sottoinsiemi disgiunti per vertici

    fscanf(fin, "%d", &k);
    triangles = malloc(sizeof(triangles) * k);
    GRAPHedges(G, a);
    for (int i = 0; i < k; i++) {
        cnt = 0;
        fscanf(fin, "%d %d %d", &triangles[i].u, &triangles[i].v, &triangles[i].w);
        if (!((triangles[i].u != triangles[i].v) && (triangles[i].u != triangles[i].w) && (triangles[i].v != triangles[i].w))){
            uscita = 1;
            break;
        }

        for (int j = 0; j < G->E; j++) {
            if (a[j].v == triangles[i].u && a[j].w == triangles[i].w){
                cnt++;
            }
            if (a[j].v == triangles[i].u && a[j].w == triangles[i].v){
                cnt++;
            }
            if (a[j].v == triangles[i].v && a[j].w == triangles[i].w){
                cnt++;
            }
        }

        if(cnt != 3){
            uscita = 1;
            break;
        }

        if(visited[triangles[i].v] > 1){
            uscita = 1;
            break;
        } else {
            visited[triangles[i].v] = 1;
        }

        if(visited[triangles[i].u] > 1){
            uscita = 1;
            break;
        } else {
            visited[triangles[i].u] = 1;
        }

        if(visited[triangles[i].w] > 1){
            uscita = 1;
            break;
        } else {
            visited[triangles[i].w] = 1;
        }
    }

    fclose(fin);
    free(visited);
    free(a);
    free(triangles);
    return !uscita;
}

static int edgeExists(Graph G, int u, int w) {
    // controllo se esiste l'arco u w
    for (link t = G->ladj[u]; t != G->z; t = t->next) {
        if (t->val == w) return 1;
    }
    return 0;
}

static void recursiveTrianglePacking(Graph G, int *visited, int *bestSol, int *sol, int *maxTriangles, int currentTriangles) {
    int found = 0; // ogni volta viene messo a 0

    // Scorri tutti i vertici del grafo
    for (int u = 0; u < G->V; u++) {
        if (visited[u]) continue; // Salta i vertici già utilizzati

        for (link vNode = G->ladj[u]; vNode != G->z; vNode = vNode->next) {
            int v = vNode->val;
            if (visited[v]) continue;

            for (link wNode = G->ladj[v]; wNode != G->z; wNode = wNode->next) {
                int w = wNode->val;
                if (visited[w] || !edgeExists(G, u, w)) continue; // Verifica se esiste il terzo lato del triangolo

                // Trovato un triangolo valido {u, v, w}
                found = 1;

                // Marca i vertici come usati
                visited[u] = visited[v] = visited[w] = 1;

                // Aggiungi il triangolo alla soluzione corrente
                sol[currentTriangles * 3 + 0] = u;
                sol[currentTriangles * 3 + 1] = v;
                sol[currentTriangles * 3 + 2] = w;

                // Richiama ricorsivamente per trovare altri triangoli
                recursiveTrianglePacking(G, visited, bestSol, sol, maxTriangles, currentTriangles + 1);

                // Backtrack: rimuovi il triangolo e libera i vertici
                visited[u] = visited[v] = visited[w] = 0;
            }
        }
    }

    // Aggiorna la soluzione migliore se non ci sono altri triangoli da aggiungere
    if (!found && currentTriangles > *maxTriangles) {
        *maxTriangles = currentTriangles;
        for (int i = 0; i < currentTriangles * 3; i++) {
            bestSol[i] = sol[i];
        }
    }
}

void GRAPHsolve(Graph G) {
    int maxTriangles = 0;
    int pos = 0;

    // soluzione molto specifica al problema dato, nel caso volessivo farlo con un algoritmo classico
    // conveniva fare prima le combinazioni_semplici dei vertici (start a G->V) andando a creare una soluzione di 3 vertici
    // poi in una vettore di vettori andavo a mettere nella posizione vettore[dim] = sol dove dim andava ad aumentare
    // ogni volta che trovavo una soluzione valida (quindi archi appartenenti ad E dati i tre vertici)

    // in seguito fare le combinazioni_semplici (start a dim --> lunghezza del vettore di collezione) con sol[pos] = i dove i sono gli indici del vettore

    int *visited = calloc(G->V, sizeof(int));
    int *sol = malloc(G->V * sizeof(int));
    int *bestSol = malloc(G->V * sizeof(int)); // Al massimo ci sono V/3 triangoli

    recursiveTrianglePacking(G, visited, bestSol, sol, &maxTriangles, pos);

    printf("Massimo numero di triangoli trovati: %d\n", maxTriangles);
    for (int i = 0; i < maxTriangles; i++) {
        printf("Triangolo %d: %d %d %d\n", i + 1, bestSol[i * 3 + 0], bestSol[i * 3 + 1], bestSol[i * 3 + 2]);
    }

    free(visited);
    free(bestSol);
    free(sol);
}
