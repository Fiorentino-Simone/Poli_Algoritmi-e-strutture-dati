#include "list.h"

// DICHIARAZIONI: per LIST ADT di prima classe
struct list { link head; link tail; int N; };

// FUNCTIONS
link NEWnode(Item val, link next){
    link x = malloc(sizeof *x);
    x->item = val;
    x->next = next;
    return x;
}

void LISTinsHead(LIST l, Item val){
    l->head = NEWnode(val, l->head);
    l->N++;
}
