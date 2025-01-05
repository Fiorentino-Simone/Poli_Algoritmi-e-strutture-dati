#include <stdlib.h>
#include "graph.h"

// DICHIARAZIONE per la lista
typedef struct node *link;
struct node {
    int v, wt;
    link next;
};

// DICHIARAZIONE dell'ADT di prima classe
struct graph {int V; int E; link *ladj; ST tab; link z;};

// DICHIARAZIONE DELLE VARIABILI GLOBALI
int countBackEdge = 0;

static Edge EDGEcreate(int v, int w, int wt){
    Edge e;
    e.v = v; e.w = w; e.wt = wt;
    return e;
}

link NEW(int v, int wt, link next){
    link x = malloc(sizeof(*x));
    x->v = v; x->wt = wt; x->next = next;
    return x;
}

Graph GRAPHinit(int V){
    Graph G;
    G = malloc(sizeof *G);
    G->V = V;
    G->E = 0;

    // inizializzo la lista delle adiacenze
    G->z = NEW(-1, -1, NULL);
    G->ladj = malloc(G->V * sizeof(link));
    for (int i = 0; i < G->V; i++) {
        G->ladj[i] = G->z;
    }
    // inizializzo la tabella di simboli
    G->tab = STinit(V);

    return G;
}

void GRAPHfree(Graph G){
    link j, next;

    // distruzione della lista delle adiacenze
    for (int i = 0; i < G->V; i++) {
        for (j = G->ladj[i]; j != G->z; j = next) {
            next = j->next;
            free(j);
        }
    }

    free(G->ladj);
    free(G->z);
    STfree(G->tab);
    free(G);
}

static void insertE(Graph G, Edge e){
    int v, w, wt;
    v = e.v; w = e.w; wt = e.wt;

    G->ladj[v] = NEW(w, wt, G->ladj[v]);
    G->E++;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt){
    insertE(G, EDGEcreate(id1, id2, wt));
}

Graph GRAPHload(FILE *fin){
    Graph G;
    int V, wt, id1, id2;
    char vertex[MAXL], vertex2[MAXL];

    fscanf(fin, "%d\n", &V);
    G = GRAPHinit(V);

    for (int i = 0; i < G->V; i++) {
        fscanf(fin, "%s", vertex);
        STinsert(G->tab, vertex, i);
    }

    while(fscanf(fin, "%s %s %d", vertex, vertex2, &wt) == 3) {
        id1 = STsearch(G->tab, vertex);
        id2 = STsearch(G->tab, vertex2);
        if (id1 != -1 && id2 != -1)
            GRAPHinsertE(G, id1, id2, wt);
    }
    return G;
}

void GRAPHedges(Graph G, Edge *a){
    int v, E = 0;
    link t;

    for (v = 0; v < G->V; v++){
        for (t = G->ladj[v]; t != G->z; t = t->next){
            a[E++] = EDGEcreate(v, t->v, t->wt); // ricordo senza if perchè grafo orientato
        }
    }
}

void GRAPHstore(Graph G, FILE *fout){
    Edge *a;
    int i;

    a = malloc(G->E * sizeof(Edge));
    if (a == NULL){
        printf("Errore nell'allocazione!");
        exit(-1);
    } 

    GRAPHedges(G, a);

    for (i = 0; i < G->E; i++){
        fprintf(fout, "(%s, %s) con peso: %d\n", STsearchByIndex(G->tab, a[i].v), STsearchByIndex(G->tab, a[i].w), a[i].wt);
    }
    free(a);
}

static void dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st, Edge *backEdges) {
    link t; 
    int v, w; 
    Edge x;

    w = e.w;
    st[e.w] = e.v;
    pre[w] = (*time)++;
    
    for (t = G->ladj[w]; t != G->z; t = t->next){
        if (pre[t->v] == -1){
            dfsR(G, EDGEcreate(w, t->v,t->wt), time, pre, post, st, backEdges);
        }
        else {
            v = t->v;
            x = EDGEcreate(w, v,t->wt);
            if (post[v] == -1){
                backEdges[countBackEdge].v = x.v;
                backEdges[countBackEdge].w = x.w;
                backEdges[countBackEdge].wt = x.wt;
                countBackEdge++;
                printf("(%s, %s) | Peso: %d\n", STsearchByIndex(G->tab, x.v), STsearchByIndex(G->tab, x.w),t->wt);
            }
        }
    }
    post[w] = (*time)++;
}

void GRAPHfindBackEdges(Graph G, int id, Edge *backEdges) {
    int v, time = 0;

    int *pre = malloc(G->V * sizeof(int));
    int *post = malloc(G->V * sizeof(int));
    int *st = malloc(G->V * sizeof(int));

    if (!pre || !post || !st || !backEdges) return;

    for (v = 0; v < G->V; v++) {
        pre[v] = post[v] = st[v] = -1;
    }

    dfsR(G, EDGEcreate(id, id, 0), &time, pre, post, st, backEdges);

    for (v = 0; v < G->V; v++) {
        if (pre[v] == -1) {
            dfsR(G, EDGEcreate(v, v, 0), &time, pre, post, st, backEdges);
        }
    }

    if (countBackEdge == 0) {
        printf("Il grafo è già un DAG.\n");
        return;
    }

    free(pre);
    free(post);
    free(st);
}

int GRAPHcount(Graph G){
    return G->V;
}

void DAGcreate(Graph G, Edge *backEdges){
    int sumWeight, maxWeight, rmb;
    sumWeight = maxWeight = rmb = 0;

    for (int i = 0; i < countBackEdge; i++) {
        sumWeight = backEdges[i].wt;
        if (sumWeight > maxWeight) {
            maxWeight = sumWeight;
            rmb = i;
        }
    }

    printf("MAX %s %s %d\n", STsearchByIndex(G->tab, backEdges[rmb].v), STsearchByIndex(G->tab, backEdges[rmb].w), backEdges[rmb].wt);

    GRAPHremoveE(G, backEdges[rmb].v, backEdges[rmb].w);
    GRAPHstore(G, stdout);
}

static void removeE(Graph G, Edge e) {
    int v, w;
    link x, p;

    v = e.v; w = e.w;

    for (x = G->ladj[v], p = NULL; x != G->z; p = x, x = x->next) {
        if (x->v == w) {
            if (x == G->ladj[v]) {
                G->ladj[v] = x->next;
            } else {
                p->next = x->next;
            }
            free(x);
            G->E--;
            return;
        }
    }
}

void GRAPHremoveE(Graph G, int id1, int id2) {
    removeE(G, EDGEcreate(id1, id2, 0));
}

static void TSdfsR(Graph D, int v, int *ts, int *pre, int *time) {
    link t; pre[v] = 0;
    for (t = D->ladj[v]; t != D->z; t = t->next)
        if (pre[t->v] == -1)
            TSdfsR(D, t->v, ts, pre, time);
    ts[(*time)--] = v;
}

static void DAGlongestpath(Graph D,int *ts,int id,int i){
    int *d;
    int j;
    int w;
    int v=id;
    link t;
    d=malloc((D->V)*sizeof(int));
    for(j=0;j<(D->V);j++){
        d[j]=-1;
    }
    d[v]=0;
    for(j=i;j<D->V;j++){
        w=ts[j];
        printf("longest %d\n",w);
        if(d[w]==-1) continue;
        for (t = D->ladj[w]; t != D->z; t = t->next){
            printf("%d %d | %d\n",w,t->v,t->wt);
            if(d[t->v]==-1 || d[w]+t->wt>d[t->v]){
                d[t->v] = d[w] + t->wt;
                for (v = 0; v < D->V; v++) printf("stima %s: %d\n", STsearchByIndex(D->tab, v), d[v]);
            }
        }
    }

    for (v = 0; v < D->V; v++)
        printf("%s: %d\n", STsearchByIndex(D->tab, v), d[v]);
    printf("\n------\n");
}

void DAGpathMax(Graph G){
    int time, *pre, *ts;

    time = (G->V)-1;
    pre = malloc((G->V) * sizeof(Graph));
    ts = malloc((G->V) * sizeof(Graph));

    for (int v = 0; v < G->V; v++){
        pre[v] = -1; ts[v] = -1;
    }
    for (int v=0; v < G->V; v++){
        if (pre[v]== -1){
            TSdfsR(G, v, ts, pre, &time);
        }
    }

    printf("DAG ordine topologico \n");
    for (int v = 0; v < G->V; v++){
        printf("%s ", STsearchByIndex(G->tab, ts[v]));
        printf("\n");
    }

    free(pre);

    for(int i = 0; i < (G->V); i++){
        DAGlongestpath(G,ts,ts[i],i);
    }
}

