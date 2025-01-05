#ifndef ESE01_ST_H
#define ESE01_ST_H

// ADT di prima classe
typedef struct symboltable *ST;

// PROTOTIPI
// creatore e distruttore
ST STinit(int maxN);
void STfree(ST st);

int STcount(ST st);

// inserimento e ricerca
int STsearch(ST st, char *vertex);
void STinsert(ST st, char *vertex, int index);

// ricerca per indice
char *STsearchByIndex(ST st, int index);

#endif //ESE01_ST_H
