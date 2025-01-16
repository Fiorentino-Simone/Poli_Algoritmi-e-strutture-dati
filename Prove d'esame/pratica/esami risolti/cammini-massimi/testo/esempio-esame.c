/* 

Esempio di soluzione che, conformemente a quanto suggerito nei testi dei temi di esame, omette parte
del programma, cioe'� le eventuali funzioni "standard", le "librerie".

Pur non potendo (ne' volendo) dare una definizione formale di "standard"/"libreria", si possono 
considerari tali le strutture dati e gli algoritmi presentati a lezione (e studiati), 
quali ad esempio:
- ordinamento per vettori
- funzioni su liste, ordinate e non,
- funzioni su FIFO, LIFO, code prioritario, BST, tabelle di hash, heap, grafi e altro visto a lezione
Non si accettano come "standard" i modelli di funzioni ricorsive per il calcolo combinatorio, 
in quanto il modello in se e' troppo generico e va integrato con la rappresentazione della soluzione, 
la gestione dei casi terminali con eventuale verifica della soluzione, l'eventuale pruning, 
i criteri per determinare la soluzione ottima, ecc.

Delle funzioni omesse, e' opportuno riportare almeno il prototipo (se funzione di ordinamento per dati
non standard, riportare anche la funzione di confronto o l'istruzione di confronto).
Di eventuali ADT utilizzati, il file header (il .h) o il suo contenuto (allegando il foglio stampato 
oppure scrivendone direttamente il contenuto, il risultato e' equivalente) 
la definizione della struct wrapper (nel caso di un ADT per collezioni) puo' essere o meno inclusa, 
in funzione di quanto la soluzione sia completamente "client" dell'ADT, oppure se ne sviluppi 
una parte, come nel caso proposto.  

In questo caso, rispetto alla soluzione completa, siccome la soluzione viene in parte realizzata 
come un'aggiunta/integrazione all'ATD Graph, di questo si rappresentano solo le aggiunte, 
omettendo la parte "standard". Piu' in dettaglio:
- si sono omessi piu' controlli di errore banali

*/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Graph.h"
#define MAXC 21

int main(int argc, char **argv) {
  int id;
  char *name, label[MAXC];
  FILE *fin;
  Graph G;

  name = argv[1];
  fin = fopen(name, "r");

  G = GRAPHload(fin);

  if (GRAPHregular(G))
    printf("The graph is regular\n");
  else
    printf("The graph is NOT regular\n");

  while(1) {
    fprintf(stdout, "\nInsert vertex name [fine to quit] > ");
    fscanf(stdin, "%s", label);
    if (!strcmp(label, "fine"))
      break;

    id = GRAPHsearchByKey(G, label);
    GRAPHlongestPath(G, id);
  }

  fclose(fin);
  GRAPHfree(G);

  return 0;
}

/*-----------------------------------------------------------*/
/* Graph.h */

typedef struct edge { int v; int w; int wt; } Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
int   GRAPHsearchByKey(Graph G, char *label);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
int   GRAPHregular(Graph G);
void  GRAPHlongestPath(Graph G, int src);

/*-----------------------------------------------------------*/
/* Graph.c */

#include "Graph.h"
#include "ST.h"

typedef struct node *link;
struct node { int v; int wt; link next; } ;
struct graph { int V; int E; link *ladj; ST tab; link z; } ;

/* ..: */
/* salto le funzioni standard:
GRAPHinit
GRAPHfree
GRAPHload
GRAPHsearchByKey
GRAPHinsertE
*/

/* faccio quelle (non standard) necessrie per questo problema */
/* funzione interna, anticipo il prototipo per scriverla dopo */

static void allPathsR(Graph G, int src, Edge *path, int *visited, int curLen, 
		      int curW, Edge *bestPath, int *bestLen, int *bestW);

/* Prima domanda - Problema di verifica: un grafo e' regolare se 
   - tutti i vertici hanno lo stesso grado in ingresso e uscita
   - questo grado e' lo stesso per tutti. 
   La prima corrisponde a quella proposta, con calcolo dei gradi effettuata dentro alla
   GRAPHregular. 
   La seconda prevede una modifica del grafo (struct wrapper, con aggiunta dei vettori in_d e 
   out_d, che vanno gestiti opportunamente in creazione e acquisizione del grafo: per questo si 
   mostra solo la parte aggiuntiva della funzione GRAPHinsertE.
 */

/* soluzione 1: in GRAPHregular si calcolano i gradi e si fa la verifica */

int  GRAPHregular(Graph G) {
  int v, *in_d, *out_d, reg=1;
  link t;

  /* vettori "paralleli" ai vertici, per in e out degree */
  in_d = malloc(G->V * sizeof(int));
  out_d = malloc(G->V * sizeof(int));

  /* inizializzazione esplicita (poteva essere sostituita, in quanto azzeramento, da calloc) */
  for (v=0; v < G->V; v++) {
    in_d[v]=0;
    out_d[v] = 0;
  }

  /* computo di in e out_degree, percorrendo una sola volta tutte le liste di adiacenza */
  for (v=0; v < G->V; v++)
    for (t=G->ladj[v]; t != G->z; t = t->next) {
      out_d[v]++;
      in_d[t->v]++;
    }

  /* verifica O(G->V), tenendo conto che non e' necessario confrontare tutti i vertici con tutti 
     gli altri, ma basta confrontarli con uno qualunque (sempre lo stesso) degli altri, in questo 
     caso il primo */
  for (v=0; v < G->V; v++)
    if ((in_d[v] != out_d[v]) || in_d[v] != in_d[0]) {
      reg = 0;
      break;
    }

  free(in_d);
  free(out_d);

  return reg;
}

/* soluzione 2: si aggiungono ai vertici le informazioni sui gradi
   in GRAPHregular2 si fa solo verifica. 
   QUESTA SOLUZIONE E' ALTERNATIVA ALLA PRECEDENTE (e' sufficiente una delle due) */

/* aggiunta al wrapper */
struct graph { int V; int E; link *ladj; ST tab; link z; 
               int *in_d, *out_d} ;

/* aggiunte a GRAPHinit e GRAPHinsertE (si omette la GRAPHfree) */
Graph GRAPHinit(int V) {
  Graph G = malloc(sizeof *G);
  /* ... */
  /* alla parte standard si aggiunge l'allocazione dei due vettori (azzerati) */
  G->in_d = calloc(G->V,sizeof(int));
  G->out_d = calloc(G->V,sizeof(int));

  return G;
}
static void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w, wt = e.wt;
  /* questa parte potrebbe essere omessa */
  G->ladj[v] = NEW(w, wt, G->ladj[v]);
  G->E++;
  /* questa è l'aggiunta per gestire i gradi */
  G->out_d[v]++; 
  G->in_d[w]++; 
}

/* fine aggiunte - ora la GRAPHregular2 */
int  GRAPHregular2(Graph G) {
  int v;

  for (v=0; v < G->V; v++)
    if ((G->in_d[v] != G->out_d[v]) || G->in_d[v] != G->in_d[0]) {
      return 0;
    }

  return 1;
}

/* Seconda domanda - Problema di ottimizzazione: lo si imposta come variante dell'enumerazione 
   dei cammini semplici: la funzione GRAPHlongestPath è la funzione wrapper, che chiama la funzione
   ricorsiva allPathsR.
 */

void GRAPHlongestPath(Graph G, int src){
  int i, *visited, len = -1, weight = 0;
  Edge *path, *bestPath;

  path = malloc(G->E * sizeof(Edge));
  bestPath = malloc(G->E * sizeof(Edge));
  visited = malloc(G->V * sizeof(int));

  if (path == NULL || bestPath == NULL || visited == NULL)
    exit(-1);

  for (i=0; i< G->V; i++)
    visited[i]=0;

  allPathsR(G, src, path, visited, 0, 0, bestPath, &len, &weight);

  if (path != NULL && len > 0) {
    for(i=0; i<len; i++)
      fprintf(stdout,"%s -- <w=%d> -- %s\n", 
	      STsearchByIndex(G->tab,path[i].v), path[i].wt, 
	      STsearchByIndex(G->tab,path[i].w));
    fprintf(stdout, "Total weight: %d\n", weight);
  }
  else
    printf("No path found...\n");

  free(visited);
  free(path);
  free(bestPath);
}

static void allPathsR(Graph G, int src, Edge *path, int *visited, int curLen, int curW, 
		      Edge *bestPath, int *bestLen, int *bestW) {
  int i, terminal = 1;
  link t;
  visited[src] = 1;

  for (t=G->ladj[src]; t != G->z; t = t->next)
    if (!visited[t->v]) {
	  path[curLen] = EDGEcreate(src, t->v, t->wt);
	  allPathsR(G, t->v, path, visited, curLen+1, curW+t->wt, bestPath, bestLen, bestW);
	  terminal = 0;
    }

  /* caso terminale scritto dopo quello ricorsivo, in quanto il caso terminale è determinato 
     per esclusione (non si riesce ad andare avanti */
  if (terminal)
    if (*bestW < curW || *bestLen == -1) {
	  *bestW = curW;
	  *bestLen = curLen;
	  for (i=0;i<curLen;i++)
        bestPath[i] = path[i];
    }

  visited[src] = 0;
  /* si noti che l'azzeramento (backtrack) di visited[src] E' la principale (se non unica differenza
     tra l'enumerazione dei cammini semplici e la visita in profondita' */ 
}



