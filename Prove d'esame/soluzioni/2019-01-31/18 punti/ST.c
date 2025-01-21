#include <stdlib.h>
#include <string.h>

#include "ST.h"

struct tableSym {
    Item *vertici;
    int size;
    int maxSize;
};

ST STinit(int maxN){
    ST table = malloc(sizeof(*table));
    table->size = 0;
    table->maxSize = maxN;
    table->vertici = calloc(maxN, sizeof(Item));
    return table;
}

void STfree(ST st){
    free(st->vertici);
    free(st);
}

int STsearchByName(ST st, char *name){
    for (int j = 0; j < st->size; j++) {
        if(strcmp(st->vertici[j].name, name) == 0){
            return j;
        }
    }
    return -1;
}

char *STsearchById(ST st, int id){
    return st->vertici[id].name;
}

void STinsert(ST st, Item i){
    if(st->size == st->maxSize){
        st->vertici = realloc(st->vertici, 2 * st->maxSize * sizeof(char *));
        st->maxSize = 2 * st->maxSize;
    }
    strcpy(st->vertici[st->size].name, i.name);
    st->size++;
}