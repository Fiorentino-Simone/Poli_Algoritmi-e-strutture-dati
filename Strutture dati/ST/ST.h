#include "Item.h"

typedef struct symboltable *ST;

ST STinit(int maxN, float r);
void STfree(ST st);

void STinsert(ST st, Item val);
Item STsearch(ST st, Key k);
void STdelete(ST st, Key k);

void STdisplay(ST st);

int STcount(ST st);
int STempty(ST st);