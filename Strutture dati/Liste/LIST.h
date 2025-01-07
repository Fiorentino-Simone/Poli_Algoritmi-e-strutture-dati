#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

// sarebbe da importare la libreria KEY.h e ITEM.h che sarebbero dei quasi ADT
typedef int Key;
typedef int Item;

typedef struct list *LIST; // ADT lista espresso come ADT di prima classe

// PROTOTIPI
// creatore e distruttore
LIST LISTinit();
void LISTfree(link h);

// inserimento
void LISTinsHead(LIST l, Item val);
link LISTinsTail(link head, Item val);

Item LISTsearch(link head, Key k);

// cancellazioni
link LISTdelhead(link head);
Item LISTextrheadP(link *hp);
link LISTdelkey(link h, Key k);
link LISTdelkeyR(link x, Key k);
Item LISTextrkeyP(link *x, Key k);

// ordinamenti
link LISTsortins(link h, Item item);
Item LISTsortsearch(link h, Key k);
link LISTsortdel(link h, Key k);

void LISTshow(link h);

#endif //LIST_H