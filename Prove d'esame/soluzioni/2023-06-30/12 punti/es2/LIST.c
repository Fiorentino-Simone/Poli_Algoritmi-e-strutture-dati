#include <stdlib.h>
#include <stdio.h>
#include "LIST.h"

typedef struct node *link;

struct node{
    int val;
    link next;
};

struct list{
    link head;
    int N;
};

static link NEWnode(int val, link next){
    link node = malloc(sizeof(*node));
    node->next = next;
    node->val = val;
    return node;
}

static link LISTinTail(int val, link h){
    link x;
    if(h == NULL){
        return NEWnode(val, NULL);
    }
    for (x = h; x->next != NULL; x = x->next);
    x->next = NEWnode(val, NULL);
    return h;
}

void LISTpopolate(LIST list){
    int val;
    list->N = 8;
    for (int i = 0; i < list->N; ++i) {
        printf("Inserisci il valore da inserire: ");
        scanf("%d", &val);
        list->head = LISTinTail(val, list->head);
    }
}

LIST LISTinit(){
    LIST list = malloc(sizeof(*list));
    list->head = NULL;
    list->N = 0;
    return list;
}

void f(LIST l) {
    int i = 0;
    // NON USIAMO LA FREE
    for (link x = l->head, p = NULL; x != NULL; i++, p = x, x = x->next){
        if (i % 3 == 0) {
            if (x == l->head){
                l->head = x->next;
            }
            else {
                p->next = x->next;
            }
            l->N--;
        }
    }
}

void LISTprint(LIST list){
    link x = list->head;
    for (int i = 0; i < list->N; i++, x = x->next) {
        printf( " %d ", x->val);
    }
    printf("\n");
}

void LISTfree(LIST list){
    link x, p;
    p = NULL;
    x = list->head;
    for (int i = 0; i < list->N; i++) {
        p = x;
        x = x->next;
        free(p);
    }
}
