#include "GRAPH.h"
#include "ST.h"
#include "QUEUE.h" // per la visita in ampiezza (coda non a priorità, FIFO)

/* #region VALIDO SOLO PER LA LISTA DELLE ADIACENZE */
typedef struct node *link;

struct node
{
    int v;
    int wt;
    link next;
};
/*#endregion*/

struct graph
{
    int V;
    int E;
    int **madj; // uso la matrice di adiacenza come rappresentazione per il grafo
    link *ladj; // uso la lista di adiacenza come rappresentazione per il grafo
    ST tab;

    // aggiungere eventuali campi per la rappresentazione
    link z;
};

/* #region VALIDO SOLO PER LA MATRICE DI ADICENZA */
static int **MATRIXint(int r, int c, int val)
{
    int i, j;
    int **t = malloc(r * sizeof(int *));
    for (i = 0; i < r; i++)
        t[i] = malloc(c * sizeof(int));

    for (i = 0; i < r; i++)
        for (j = 0; j < c; j++)
            t[i][j] = val;
    return t;
}
/*#endregion*/

/* #region VALIDO SOLO PER LA LISTA DI ADICENZA */
static link NEW(int v, int wt, link next)
{
    link x = malloc(sizeof *x);
    x->v = v;
    x->wt = wt;
    x->next = next;
    return x;
}
/*#endregion*/

Graph GRAPHinit(int V)
{
    Graph G = malloc(sizeof *G);
    G->V = V;
    G->E = 0;

    G->madj = MATRIXint(V, V, 0); // inizializzo la matrice di adiacenza con 0 (matrice quadrata V x V)

    G->z = NEW(-1, -1, NULL); // nodo sentinella
    G->ladj = malloc(V * sizeof(link));
    for (int v = 0; v < V; v++)
        G->ladj[v] = G->z; // inizializzo la lista di adiacenza con il nodo sentinella

    G->tab = STinit(V);
    return G;
}

void GRAPHfree(Graph G)
{
    int i;
    int v;
    link t, next;

    // per la matrice di adiacenza
    for (i = 0; i < G->V; i++)
        free(G->madj[i]);
    free(G->madj);

    // per la lista di adiacenza
    for (v = 0; v < G->V; v++)
    {
        for (t = G->ladj[v]; t != G->z; t = next)
        {
            next = t->next;
            free(t);
        }
    }
    free(G->ladj);
    free(G->z);

    STfree(G->tab);
    free(G);
}

Graph GRAPHload(FILE *fin)
{
    int V, i, id1, id2, wt;
    char label1[MAXC], label2[MAXC];
    Graph G;

    fscanf(fin, "%d", &V);
    G = GRAPHinit(V);
    for (i = 0; i < V; i++)
    {
        fscanf(fin, "%s", label1);
        STinsert(G->tab, label1, i); // inserisci nel tabella di simboli la label nella posizione i (ES: a[i] = strdup(label1))
    }

    while (fscanf(fin, "%s %s %d", label1, label2, &wt) == 3)
    {
        id1 = STsearch(G->tab, label1);
        id2 = STsearch(G->tab, label2);
        if (id1 != -1 && id2 != -1)
            GRAPHinsertE(G, id1, id2, wt);
    }

    return G;
}

void GRAPHstore(Graph G, FILE *fout)
{
    int i;
    Edge *a;
    a = malloc(G->E * sizeof(Edge));
    GRAPHedges(G, a); // dipende dalla rappresentazione
    fprintf(fout, "%d\n", G->V);
    for (i = 0; i < G->V; i++)
        fprintf(fout, "%s\n", STsearchByIndex(G->tab, i)); // ho la dipendenza indice - dato (con la label univoca)
    for (i = 0; i < G->E; i++)
        fprintf(fout, "%s  %s %d\n", STsearchByIndex(G->tab, a[i].v), STsearchByIndex(G->tab, a[i].w), a[i].wt);
}

static Edge EDGEcreate(int v, int w, int wt)
{
    Edge e;
    e.v = v;
    e.w = w;
    e.wt = wt;
    return e;
}

static void insertE(Graph G, Edge e)
{
    int v = e.v, w = e.w, wt = e.wt;

    // matrice di adiacenza
    if (G->madj[v][w] == 0)
        G->E++;

    G->madj[v][w] = 1;  // se non ho un grafo pesato
    G->madj[v][w] = wt; // se ho un grafo pesato

    // se il grafo è non orientato (matrice simmetrica)
    G->madj[w][v] = 1;
    G->madj[w][v] = wt;

    // lista di adiacenza
    G->ladj[v] = NEW(w, wt, G->ladj[v]); // inserisco in testa

    // se il grafo è non orientato
    G->ladj[w] = NEW(v, wt, G->ladj[w]);

    // G->E++;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt)
{
    insertE(G, EDGEcreate(id1, id2, wt));
}

static void removeE(Graph G, Edge e)
{
    int v = e.v, w = e.w;
    link x, p;

    // matrice di adiacenza
    if (G->madj[v][w] != 0)
        G->E--;

    G->madj[v][w] = 0; // metto peso nullo per indicare l'assenza dell'arco incidente in v e w
    // se il grafo è non orientato (matrice simmetrica)
    G->madj[w][v] = 0;

    // lista di adiacenza
    for (x = G->ladj[v], p = NULL; x != G->z; p = x, x = x->next)
    {
        if (x->v == w)
        {
            if (x == G->ladj[v])
                G->ladj[v] = x->next; // se l'arco da eliminare è la testa
            else
                p->next = x->next;
            break;
        }
    }

    /*
        se il grafo non è orientato ho bisogno di eliminare anche l'arco da w a v
        for (x = G->ladj[w], p = NULL; x != G->z; p = x, x = x->next)
        {
            if (x->v == v)
            {
                if (x == G->ladj[w])
                    G->ladj[w] = x->next; // se l'arco da eliminare è la testa
                else
                    p->next = x->next;
                break;
            }
        }
    */

    // G->E--;
    free(x);
}

void GRAPHremoveE(Graph G, int id1, int id2)
{
    removeE(G, EDGEcreate(id1, id2, 0));
}

int GRAPHgetIndex(Graph G, char *label)
{
    int id;
    id = STsearch(G->tab, label);
    if (id == -1)
    {
        id = STcount(G->tab);
        STinsert(G->tab, label, id);
    }
    return id;
}

void GRAPHedges(Graph G, Edge *a)
{
    int v, w, E = 0;

    // matrice di adiacenza
    for (v = 0; v < G->V; v++)
    {
        for (w = 0; w < G->V; w++)
        { // se il grafo non è orientato posso fare w = v + 1
            if (G->madj[v][w] != 0)
            {
                a[E++] = EDGEcreate(v, w, G->madj[v][w]);
            }
        }
    }

    // lista di adiacenza
    for (v = 0; v < G->V; v++)
    {
        for (link t = G->ladj[v]; t != G->z; t = t->next)
        {
            // se il grafo è non orientato bisogna wrappare l'istruzione con un if (v < t->v)
            a[E++] = EDGEcreate(v, t->v, t->wt);
        }
    }

    return;
}

static int pathR(Graph G, int v, int w, int *visited)
{
    int t;
    if (v == w)
    {
        return 1; // ho trovato il cammino
    }

    visited[v] = 1;
    for (t = 0; t < G->V; t++)
    { // scorro la riga di v
        if (G->madj[v][t] == 1)
        {
            if (visited[t] == 0)
            { // se l'arco esiste, controllo che il vertice t non sia già stato visitato
                if (pathR(G, t, w, visited))
                {
                    printf("(%s, %s) in path\n", STsearchByIndex(G->tab, v), STsearchByIndex(G->tab, t));
                    return 1;
                }
            }
        }
    }

    return 0;
}

void GRAPHpath(Graph G, int id1, int id2)
{
    int found, *visited;
    visited = calloc(G->V, sizeof(int));
    if (id1 == -1 || id2 == -1)
        return;

    found = pathR(G, id1, id2, visited);
    if (found == 0)
        printf("\n Pathnot found!\n");
}

static int pathRH(Graph G, int v, int w, int d, int *visited)
{
    // il parametro d serve per evitare cicli
    int t;
    if (v == w)
    {
        if (d == 0)
            return 1; // ho trovato il cammino
        else
            return 0; // non ho trovato il cammino, siccome d contiene il numero di vertici ancora da visitare
    }

    visited[v] = 1;
    for (t = 0; t < G->V; t++)
    {
        if (G->madj[v][t] == 1)
        {
            if (visited[t] == 0)
            {
                if (pathRH(G, t, w, d - 1, visited))
                {
                    printf("(%s, %s) in path\n", STsearchByIndex(G->tab, v), STsearchByIndex(G->tab, t));
                    return 1;
                }
            }
        }
    }
    visited[v] = 0; // backtracking

    return 0;
}

void GRAPHpathH(Graph G, int id1, int id2)
{
    int t, found, *visited;
    visited = calloc(G->V, sizeof(int));
    if (id1 == -1 || id2 == -1)
        return;

    found = pathRH(G, id1, id2, G->V - 1, visited);
    if (found == 0)
        printf("\n Pathnot found!\n");
}

static void dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st)
{
    // funzione ricorsiva che passato un vertice v, visita tutti i vertici adiacenti a v (visita in profondità)
    link t;
    int v, w = e.w;
    Edge x;

    if (e.v != e.w)
    {
        // if obbligatorio per evitare di stampare il vertice di partenza (vertice fittizio)
        printf("(%s, %s):  T \n", STsearchByIndex(G->tab, e.v), STsearchByIndex(G->tab, e.w));
    }

    st[e.w] = e.v;      // vettore dei padri
    pre[w] = (*time)++; // aggiorno il tempo di visita (vettore dei tempi di scoperta)

    for (t = G->ladj[w]; t != G->z; t = t->next)
    {
        if (pre[t->v] == -1)
        { // se il vertice non è stato visitato
            dfsR(G, EDGEcreate(w, t->v), time, pre, post, st);
        }
        else
        {
            v = t->v;
            x = EDGEcreate(w, v);

            // solo per grafi non orientati solo B, siccome essi non hanno archi F, C
            if (pre[w] < pre[v])
            {
                // arco BACK siccome w < v
                printf("(%s, %s):  B \n", STsearchByIndex(G->tab, x.v), STsearchByIndex(G->tab, x.w));
            }

            // valido solo per i grafi orientati, con archi B, F, C
            if (post[v] == -1)
            {
                // arco BACK
                printf("(%s, %s):  B \n", STsearchByIndex(G->tab, x.v), STsearchByIndex(G->tab, x.w));
            }
            else if (pre[v] > pre[w])
            {
                // arco FORWARD
                printf("(%s, %s):  F \n", STsearchByIndex(G->tab, x.v), STsearchByIndex(G->tab, x.w));
            }
            else
            {
                // arco CROSS
                printf("(%s, %s):  C \n", STsearchByIndex(G->tab, x.v), STsearchByIndex(G->tab, x.w));
            }
            post[w] = (*time)++;
        }
    }
}

void GRAPHdfs(Graph G, int id)
{
    // visita in profondità (dfs): visita tutti i vertici del grafo
    int v, time = 0, *pre, *post, *st;

    pre = malloc(G->V * sizeof(int));
    post = malloc(G->V * sizeof(int));
    st = malloc(G->V * sizeof(int));
    for (v = 0; v < G->V; v++)
    {
        pre[v] = -1;
        post[v] = -1;
        st[v] = -1;
    }

    dfsR(G, EDGEcreate(id, id), &time, pre, post, st);
    for (v = 0; v < G->V; v++)
    {
        if (pre[v] == -1)
        {
            dfsR(G, EDGEcreate(v, v), &time, pre, post, st);
        }
    }

    printf("discovery / endprocessing time labels \n");
    for (v = 0; v < G->V; v++)
        printf("%s:%d / %d\n", STsearchByIndex(G->tab, v), pre[v], post[v]);
    printf("resulting DFS tree \n");
    for (v = 0; v < G->V; v++)
        printf("%s's parent: %s \n", STsearchByIndex(G->tab, v), STsearchByIndex(G->tab, st[v]));
}

static void bfsR(Graph G, Edge e, int *time, int *pre, int *st, int *dist)
{
    int x;

    Q q = Qinit();
    Qput(q, e);
    dist[e.v] = -1;

    while (!Qempty(q))
    {
        if (pre[(e = Qget(q)).w] == -1) // il vertice w è stato visitato?
        {
            pre[e.w] = (*time)++;      // tempo di visita
            st[e.w] = e.v;             // vettore dei padri
            dist[e.w] = dist[e.v] + 1; // distanza tra il vertice sorgente e il vertice w

            // inserisce tutti gli archi incidenti in w, che abbiano il vertice x non ancora visitato
            for (x = 0; x < G->V; x++)
            {
                if (G->madj[e.w][x] == 1)
                {
                    if (pre[x] == -1)
                    {
                        Qput(q, EDGEcreate(e.w, x));
                    }
                }
            }
        }
    }
}

void GRAPHbfs(Graph G, int id)
{
    // visita in ampiezza: determina tutti i vertici raggiungibili da un vertice sorgente
    // quindi NON visita tutti i vertici del grafo necessariamente (a differenza della visita in profondità)

    // ATTENZIONE:
    // la visita in ampiezza determina la minima distanza tra s e ogni vertice raggiungibile da esso --> CAMMINO MINIMO SEMPLICE, con
    // il minor numero di vertici attraversati --> attenzione non è detto che sia il cammino minimo in termini di peso degli archi (siccome archi di peso unitario)

    int v, time = 0, *pre, *st, *dist;

    pre = malloc(G->V * sizeof(int));
    st = malloc(G->V * sizeof(int));
    dist = malloc(G->V * sizeof(int)); // permette di tenere traccia della distanza tra il vertice sorgente e il vertice v
    for (v = 0; v < G->V; v++)
    {
        pre[v] = -1;
        st[v] = -1;
        dist[v] = INT_MAX;
    }

    bfsR(G, EDGEcreate(id, id), &time, pre, st, dist);

    printf("\n Resulting BFS tree \n");
    for (v = 0; v < G->V; v++)
        if (st[v] != -1)
            printf("%s's parentis:%s\n", STsearchByIndex(G->tab, v), STsearchByIndex(G->tab, st[v]));
    printf("\n Levelizing \n");
    for (v = 0; v < G->V; v++)
        if (st[v] != -1)
            printf("%s: %d \n", STsearchByIndex(G->tab, v), dist[v]);
}

static void dfsRcc(Graph G, int v, int id, int *cc)
{
    link t;
    cc[v] = id;
    for (t = G->ladj[v]; t != G->z; t = t->next)
        if (cc[t->v] == -1)
            dfsRcc(G, t->v, id, cc);
}

int GRAPHcc(Graph G)
{
    int v, id = 0, *cc;

    cc = malloc(G->V * sizeof(int));
    for (v = 0; v < G->V; v++)
        cc[v] = -1;

    for (v = 0; v < G->V; v++)
        if (cc[v] == -1)
            dfsRcc(G, v, id++, cc); // avro un vettore di c dove c[i] = id della componente connessa a cui appartiene il vertice i
    printf("Connectedcomponent(s) \n");
    for (v = 0; v < G->V; v++)
        printf("node%s in cc %d\n", STsearchByIndex(G->tab, v), cc[v]);
    return id;
}

static void SCCdfsR(Graph G, int w, int *scc, int *time0, int time1, int *post)
{
    link t;
    scc[w] = time1;
    for (t = G->ladj[w]; t != G->z; t = t->next)
        if (scc[t->v] == -1)
            SCCdfsR(G, t->v, scc, time0, time1, post);
    post[(*time0)++] = w;
}

Graph GRAPHreverse(Graph G)
{
    int v;
    link t;
    Graph R = GRAPHinit(G->V);
    for (v = 0; v < G->V; v++)
        for (t = G->ladj[v]; t != G->z; t = t->next)
            GRAPHinsertE(R, t->v, v);
    return R;
}

int GRAPHscc(Graph G)
{
    int v, time0 = 0, time1 = 0, *sccG, *sccR, *postG, *postR;
    Graph R = GRAPHreverse(G);

    sccG = malloc(G->V * sizeof(int));
    sccR = malloc(G->V * sizeof(int));
    postG = malloc(G->V * sizeof(int));
    postR = malloc(G->V * sizeof(int));
    for (v = 0; v < G->V; v++)
    {
        sccG[v] = -1;
        sccR[v] = -1;
        postG[v] = -1;
        postR[v] = -1;
    }

    for (v = 0; v < G->V; v++)
        if (sccR[v] == -1)
            SCCdfsR(R, v, sccR, &time0, time1, postR);
    time0 = 0;
    time1 = 0;
    for (v = G->V - 1; v >= 0; v--)
    {
        if (sccG[postR[v]] == -1) // decrescente per tempi di fine visita di G trasposto
        {
            SCCdfsR(G, postR[v], sccG, &time0, time1, postG);
            time1++;
        }
    }
    printf("strongly connected components\n");
    for (v = 0; v < G->V; v++)
        printf("node%s in scc%d\n", STsearchByIndex(G->tab, v), sccG[v]);
    return time1;
}