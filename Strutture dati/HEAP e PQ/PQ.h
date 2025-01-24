#include "Item.h"

typedef struct pqueue *PQ;

PQ PQinit(int maxN);
void PQfree(PQ pq);

int PQempty(PQ pq);
int PQsize(PQ pq);
Item PQshowMax(PQ pq);
void PQdisplay(PQ pq);

void PQinsert(PQ pq, Item val);

Item PQextractMax(PQ pq);

void PQchange(PQ pq, Item val);