#ifndef BST_H
#define BST_H

#include <stdio.h>
#include <stdlib.h>

// sarebbe da importare la libreria KEY.h e ITEM.h che sarebbero dei quasi ADT
typedef int Key;
typedef int Item;

typedef struct ST; // ADT di prima classe sui dizionari (tabella di simboli, sarebbe da importare)

typedef struct binarysearchtree *BST; // BST completo

// PROTOTIPI
// creatore e distruttore
BST BSTinit();
void BSTfree(BST bst);

// operazioni
int BSTcount(BST bst);
int BSTempty(BST bst);
Item BSTsearch(BST bst, Key k);
Item BSTmin(BST bst);
Item BSTmax(BST bst);

// inserimento e cancellazione
void BSTinsert_leafR(BST bst, Item x);
void BSTinsert_leafI(BST bst, Item x);
void BSTinsert_root(BST bst, Item x);
void BSTdelete (BST bst, Key k);
Item BSTselect (BST bst, int r);

// visita e rotazioni
void BSTvisit(BST bst, int strategy);
link rotR(link h);
link rotL(link h);
link partR(link h, int r);
Item BSTsucc(BST bst, Key k);
Item BSTpred(BST bst, Key k);

#endif //BST_H