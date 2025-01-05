#ifndef ESE02_ST_H
#define ESE02_ST_H

// ADT di prima classe
typedef struct symboltable *ST;

// PROTOTIPI
// creatore e distruttore
ST STinit(int maxN);
void STfree(ST st);

int STcount(ST st);

// inserimento e ricerca
int STsearch(ST st, char *name);
void STinsert(ST st, char *name, char *subnet);

// ricerca per indice
char *STsearchByIndexName(ST st, int index);
char *STsearchByIndexSubnet(ST st, int index);

// ricerca per nome
int STsearchByName(ST st, char *name);

// ordinamento
void STsort(ST st, int *a);

#endif //ESE02_ST_H
