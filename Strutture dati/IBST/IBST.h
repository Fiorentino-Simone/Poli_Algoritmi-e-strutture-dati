#include <stdio.h>
#include <stdlib.h>

#include "Item.h"

typedef struct intervalbinarysearchtree *IBST;

IBST IBSTinit();
void IBSTfree(IBST ibst);

void IBSTinsert(IBST ibst, Item x);
void IBSTdelete(IBST ibst, Item x);
Item IBSTsearch(IBST ibst, Item x);

int IBSTcount(IBST ibst);
int IBSTempty(IBST ibst);

void IBSTvisit(IBST ibst, int strategy);