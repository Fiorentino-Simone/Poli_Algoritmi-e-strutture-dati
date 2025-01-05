#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>

typedef int Key;
typedef int Item;

typedef struct node *link;
struct node { Item item; link next; };
typedef struct list *LIST;

link NEWnode(Item val, link next);
void LISTinsHead(LIST l, Item val);
link LISTinsTail(link head, Item val);
Item LISTsearch(link head, Key k);
link LISTdelhead(link h);
Item LISTextrheadP(link *hp);
link LISTdelkey(link h, Key k);
link LISTdelkeyR(link x, Key k);
Item LISTextrkeyP(link *x, Key k);
link LISTsortins(link h, Item item);
Item LISTsortsearch(link h, Key k);
link LISTsortdel(link h, Key k);
void LISTshow(link h);
void LISTfree(link h);

#endif //LIST_H