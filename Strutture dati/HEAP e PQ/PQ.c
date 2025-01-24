#include <stdlib.h>
#include "Item.h"
#include "ST.h"
#include "PQ.h"

typedef struct
{
    int index;
    int prio;
} heapItem; // PQ gestisce la coppia (indice, priorità)

struct pqueue
{
    heapItem *A;
    ST hash; // tabella hash per la gestione degli indici (O(1)), si potrebbe fare a meno ma lo facciamo per la PQchange
    int *qp; // memorizza la posizione di un indice all'interno dell'heap
    int heapsize;
};

static int LEFT(int i) { return (i * 2 + 1); }
static int RIGHT(int i) { return (i * 2 + 2); }
static int PARENT(int i) { return ((i - 1) / 2); }

PQ PQinit(int maxN)
{
    int i;
    PQ pq = malloc(sizeof(*pq));
    pq->heap = malloc(maxN * sizeof(heapItem));
    pq->hash = STinit(maxN);
    pq->qp = malloc(STsize(pq->hash) * sizeof(int));

    for (i = 0; i < maxN; i++)
        pq->heap[i].index = -1;
    for (i = 0; i < STsize(pq->hash); i++)
        pq->qp[i] = -1;
    pq->heapsize = 0;
    return pq;
}

void PQfree(PQ pq)
{
    free(pq->qp);
    STfree(pq->hash);
    free(pq->heap);
    free(pq);
}

int PQempty(PQ pq)
{
    return pq->heapsize == 0;
}

int PQsize(PQ pq)
{
    return pq->heapsize;
}

Item PQshowMax(PQ pq)
{
    return STsearch(pq->hash, pq->heap[0].index);
}

void PQdisplay(PQ pq)
{
    int i;
    for (i = 0; i < pq->heapsize; i++)
        ITEMshow(pq->heap[i]);
}

void PQinsert(PQ pq, Item item)
{
    int i, index, prio;
    index = STinsert(pq->hash, item);
    prio = STgetPrio(pq->hash, index);
    i = pq->heapsize++;
    while ((i >= 1) && (pq->heap[PARENT(i)].prio) < prio)
    {
        pq->heap[i] = pq->heap[PARENT(i)]; // risalgo l'heap cercando la posizione corretta
        pq->qp[pq->heap[i].index] = i;
        i = PARENT(i);
    }
    pq->heap[i].index = index; // memorizzo il dato nella posizione corretta
    pq->heap[i].prio = prio;
    pq->qp[index] = i; // aggiorno qp
}

static void Swap(PQ pq, int pos1, int pos2)
{
    heapItem temp;
    int index1, index2;
    temp = pq->heap[pos1];
    pq->heap[pos1] = pq->heap[pos2];
    pq->heap[pos2] = temp;
    // update correspondence index-pos
    index1 = pq->heap[pos1].index;
    index2 = pq->heap[pos2].index;
    pq->qp[index1] = pos1;
    pq->qp[index2] = pos2;
}

static void Heapify(PQ pq, int i)
{
    int l, r, largest;
    l = LEFT(i);
    r = RIGHT(i);
    if (l < pq->heapsize && (pq->heap[l].prio > pq->heap[i].prio))
        largest = l;
    else
        largest = i;
    if (r < pq->heapsize && (pq->heap[r].prio > pq->heap[largest].prio))
        largest = r;
    if (largest != i)
    {
        Swap(pq, i, largest);
        Heapify(pq, largest);
    }
}

Item PQextractMax(PQ pq)
{
    int index;
    Item item;
    item = STgetItem(pq->hash, pq->heap[0].index);
    STdelete(pq->hash, item);
    Swap(pq, 0, pq->heapsize - 1);
    index = pq->heap[pq->heapsize - 1].index;
    pq->qp[index] = -1;
    pq->heapsize--;
    pq->heap[pq->heapsize].index = -1; // ridondante siccome l'indice non è più valido
    Heapify(pq, 0);
    return item;
}

/*void PQchange(PQ pq, Item val)
{
    int i, found = 0, pos;
    for (i = 0; i < pq->heapsize && found == 0; i++)
        if (NAMEcmp(NAMEget(&(pq->A[i])), NAMEget(&val)) == 0)
        {
            found = 1;
            pos = i;
        }
    if (found == 1)
    {
        while (pos >= 1 && PRIOget(pq->A[PARENT(pos)]) < PRIOget(val))
        {
            pq->A[pos] = pq->A[PARENT(pos)];
            pos = (pos - 1) / 2;
        }
        pq->A[pos] = val;
        Heapify(pq, pos);
    }
    else
        printf("key not found!\n");
    return;
}*/

void PQchange(PQ pq, Item item)
{
    int index, prio, pos;
    heapItem temp;
    index = STsearch(pq->hash, item);
    if (index == -1)
    {
        printf("Item not found!\n");
        return;
    }
    else
        printf("found at index %d\n", index);
    prio = PRIOget(item);
    STchangePrio(pq->hash, index, prio); // cambio la priorità nella tabella hash
    
    pos = pq->qp[index];
    temp = pq->heap[pos];
    temp.prio = prio; // new prio

    while ((pos >= 1) && (pq->heap[PARENT(pos)].index < prio))
    {
        pq->heap[pos] = pq->heap[PARENT(pos)];
        pq->qp[pq->heap[pos].index] = pos;
        pos = PARENT(pos);
    }
    pq->heap[pos] = temp; // posizionamento corretto in risalita e aggiorno heap e qp
    pq->qp[index] = pos;
    Heapify(pq, pos); // risalgo l'heap (in discesa)
}