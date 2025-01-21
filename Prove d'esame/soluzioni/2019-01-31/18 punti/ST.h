#ifndef INC_18_PUNTI_ST_H
#define INC_18_PUNTI_ST_H

#define MAXL 20

typedef struct tableSym *ST;

typedef struct {
    char name[MAXL];
} Item;

ST STinit(int maxN);
void STfree(ST st);

int STsearchByName(ST st, char *name);
char *STsearchById(ST st, int id);
void STinsert(ST st, Item i);

#endif //INC_18_PUNTI_ST_H
