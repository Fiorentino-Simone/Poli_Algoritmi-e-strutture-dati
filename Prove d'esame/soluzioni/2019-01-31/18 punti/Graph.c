#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "Graph.h"

struct grafo {
    int V, E;
    int **matradj;
    ST table;
};

Graph GRAPHinit(int nV){
    Graph G = malloc(sizeof(*G));
    G->V = nV;
    G->E = 0;
    G->matradj = calloc(nV, sizeof (int*));
    for (int i = 0; i < nV; i++) {
        G->matradj[i] = calloc(nV, sizeof (int));
    }
    G->table = STinit(nV);
    return G;
}

void GRAPHfree(Graph G){
    for (int i = 0; i < G->V; i++) {
        free(G->matradj[i]);
    }
    free(G->matradj);
    STfree(G->table);
    free(G);
}

static Edge EdgeCreate(int id1 ,int id2){
    Edge e;
    e.v = id1;
    e.w = id2;
    return e;
}

static void insertE(Graph G, Edge e){
    int v = e.v, w = e.w;
    if(G->matradj[v][w] == 0)
        G->E++;
    G->matradj[v][w] = 1;
}

void GRAPHinsertE(Graph G, int id1, int id2){
    insertE(G, EdgeCreate(id1, id2));
}

Graph GRAPHload(FILE *fin){
    ST st = STinit(20);
    Graph G;
    char v1[MAXL];
    char v2[MAXL];
    int id1, id2;
    int cnt = 0;
    Item item;

    while(fscanf(fin, "%s %s", v1, v2) == 2){
        id1 = STsearchByName(st, v1);
        id2 = STsearchByName(st, v2);
        if(id1 == -1){
            strcpy(item.name, v1);
            STinsert(st, item);
            cnt++;
        }
        if(id2 == -1){
            strcpy(item.name, v2);
            STinsert(st, item);
            cnt++;
        }
    }
    G = GRAPHinit(cnt);
    G->table = st;
    rewind(fin);
    while(fscanf(fin, "%s %s", v1, v2) == 2){
        id1 = STsearchByName(G->table, v1);
        id2 = STsearchByName(G->table, v2);
        GRAPHinsertE(G, id1, id2);
    }
    return G;
}

void GRAPHprintmatrix(Graph G){
    for(int i=0; i<G->V; i++){
        for(int j=0; j <G->V; j++)
            printf("%3d ",G->matradj[i][j]);
        printf("\n");
    }
}

int *kernelRead(FILE *fin, Graph G, int *cnt){
    char v[MAXL];
    int *sol;
    while(fscanf(fin, "%s", v) == 1){
        (*cnt)++;
    }
    rewind(fin);
    sol = calloc(*cnt, sizeof(int));
    for (int i = 0; i < *cnt; i++) {
        fscanf(fin, "%s", v);
        sol[i] = STsearchByName(G->table, v);
    }
    return sol;
}

static int appartiene(int *sol, int cnt, int i){
    for (int j = 0; j < cnt; j++) {
        if(sol[j] == i){
            return 1;
        }
    }
    return 0;
}

int isKernel(Graph G, int *sol, int cnt){
    int flag = 0;

    // controllo che i vertici passati, del possibile kernel, non abbiano archi che li congiungano
    for (int i = 0; i < cnt; i++) {
        for (int j = 0; j < cnt; j++) {
            if(G->matradj[sol[i]][sol[j]] != 0 || G->matradj[sol[j]][sol[i]] != 0){
                return 0;
            }
        }
    }

    // controllo che presi i vertici V - K essi siano collegati con un vertice del kernel
    for (int i = 0; i < G->V; i++) {
        if(!appartiene(sol, cnt, i)){
            flag = 0;
            for (int j = 0; j < cnt && flag == 0; j++) {
                if(G->matradj[sol[j]][i] != 0){
                    flag = 1;
                }
            }
            if(flag == 0){
                return 0;
            }
        }
    }
    return 1;
}

static void comb_sempl(int pos, int start, int k, int *stop, int *sol, Graph G){
    if(pos >= k){
        if(isKernel(G, sol, k)){
            (*stop) = 1;
            printf(" K = {");
            for (int i = 0; i < k; i++) {
                printf(" %s ", STsearchById(G->table, sol[i]));
            }
            printf("}");
        }
        return;
    }

    for (int i = start; i < G->V; ++i) {
        sol[pos] = i;
        comb_sempl(pos+1, i+1, k, stop, sol, G);
    }
}

static int isVertexKernel(int v, int *sol, int k){
    for (int i = 0; i < k; i++) {
        if(sol[i] == v){
            return 1;
        }
    }
    return 0;
}

static void pathR(Graph G, int *sol, int k, int *maxNodi, int *visited, int v, int w, int cnt, int *path, int *bestPath){
    if (v == w){
        if(cnt > *(maxNodi)){
            (*maxNodi) = cnt;
            for (int i = 0; i < G->V; i++) {
                bestPath[i] = path[i];
            }
        }
        return;
    }

    // voglio trovare il cammino semplice che passi per più vertici appartenenti al Kernel possibili
    if(isVertexKernel(v, sol, k)) {
        cnt++;
    }
    visited[v] = 1;
    path[v] = 1;
    for (int t = 0; t < G->V; t++) {
        if(G->matradj[v][t] == 1){
            if(visited[t] == 0){
                pathR(G, sol, k, maxNodi, visited, t, w, cnt, path, bestPath);
            }
        }
    }
    path[v] = 0;
    visited[v] = 0;
}

static void GRAPHpath(Graph G, int *sol, int k){
    int *visited, *path, *bestPath;
    int maxNodi = 0;
    int cnt = 0;
    visited = calloc(G->V, sizeof (int));
    path = malloc(G->V * sizeof (int));
    bestPath = malloc(G->V * sizeof (int));
    
    for (int v = 0; v < G->V; v++) {
        for (int w = 0; w < G->V; w++) {
            pathR(G, sol, k, &maxNodi, visited, v, w, cnt, path, bestPath);
        }
    }

    printf("\nIl cammino semplice che attraversa il maggior numero di nodi del kernel passa per %d nodi del kernel.\n", maxNodi);
    printf("\n");
    for (int i = 0; i < G->V; i++) {
        if(bestPath[i] == 1){
            printf(" %s ", STsearchById(G->table, i));
        }
    }
    free(visited);
}

void GRAPHKernelMin(Graph G){
    int stop = 0;
    int pos = 0;
    int start = 0;
    int *sol;
    int k;

    for (k = 1; k < G->V && stop == 0; k++) {
        sol = calloc(k, sizeof (int));
        comb_sempl(pos, start, k, &stop, sol, G);
    }

    GRAPHpath(G, sol, k);

    free(sol);
}