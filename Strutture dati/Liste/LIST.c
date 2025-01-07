#include "list.h"

// DEFINIZIONI: node (quasi ADT) e list (ADT di prima classe)
typedef struct node *link;
struct node { Item item; link next; };
struct list { link head; int N; };

// FUNCTIONS
static link NEWnode(Item val, link next){
    link x = malloc(sizeof *x);
    x->item = val;
    x->next = next;
    return x;
}

LIST LISTinit(){
    LIST l = malloc(sizeof *l);
    l->head = NULL;
    l->N = 0;
    return l;
}

void LISTfree(link h){
    if (h == NULL) return;
    LISTfree(h->next);
    free(h);

    // senno con ciclo while (non ricorsivo)
    // link x = h;
    // while (x != NULL){
    //     link t = x;
    //     x = x->next;
    //     free(t);
    // }
}

void LISTinsHead(LIST l, Item val){
    l->head = NEWnode(val, l->head);
    l->N++;
}

link LISTinsTail(link head, Item val){
    if(head == NULL) return NEWnode(val, NULL);
    head->next = LISTinsTail(head->next, val);
    return head;
}

Item LISTsearch(link head, Key k){
    for (link x = head; x != NULL; x = x->next){
        if (KEYcompare(KEYget(x->item), k) == 0){
            return x->item;
        }
    }
    return NULLitem();
}

link LISTdelhead(link head){
    link x = head->next;
    free(head);
    return x;
}

Item LISTextrheadP(link *hp){
    // funzione che estrae l'elemento in testa alla lista
    // e lo restituisce come Item
    if (*hp == NULL) return NULLitem();
    link x = *hp;
    Item val = x->item;
    *hp = x->next;
    free(x);
    return val;
}

link LISTdelkey(link h, Key k){
    // funzione che cancella il primo nodo con chiave k
    // e restituisce il puntatore al nodo successivo
    link x, p;
    for (x = h, p = NULL; x != NULL; p = x, x = x->next){
        if (KEYcompare(KEYget(x->item), k) == 0){
            if (p == NULL){
                h = x->next;
            } else {
                p->next = x->next;
            }
            free(x);
            return h;
        }
    }
    return h;
}

link LISTdelkeyR(link x, Key k){
    // variante ricorsiva di LISTdelkey
    if (x == NULL) return NULL;
    if (KEYcompare(KEYget(x->item), k) == 0){
        link t = x->next;
        free(x);
        return t;
    }
    x->next = LISTdelkeyR(x->next, k);
    return x;
}

Item LISTextrkeyP(link *x, Key k){
    // funzione che estrae l'elemento con chiave k
    // e lo restituisce come Item in maniera iterativa
    link p, t;
    for (p = NULL, t = *x; t != NULL; p = t, t = t->next){
        if (KEYcompare(KEYget(t->item), k) == 0){
            if (p == NULL){
                *x = t->next;
            } else {
                p->next = t->next;
            }
            Item val = t->item;
            free(t);
            return val;
        }
    }
}

link LISTsortins(link h, Item item){
    // funzione che inserisce un nodo in una lista ordinata (per chiave)
    link x, p;
    for (x = h, p = NULL; x != NULL; p = x, x = x->next){
        if (KEYcompare(KEYget(x->item), KEYget(item)) > 0){
            break;
        }
    }
    link new = NEWnode(item, x);
    if (p == NULL){
        return new;
    } else {
        p->next = new;
        return h;
    }
}

Item LISTsortsearch(link h, Key k){
    // TODO: da verificare
    // funzione che cerca un nodo in una lista ordinata (per chiave)
    for (link x = h; x != NULL; x = x->next){
        if (KEYcompare(KEYget(x->item), k) == 0){
            return x->item;
        }
        if (KEYcompare(KEYget(x->item), k) > 0){
            break;
        }
    }
    return NULLitem();
}

link LISTsortdel(link h, Key k){
    // funzione che cancella il primo nodo con chiave k
    // e restituisce il puntatore aggiornato alla lista
    link x, p;
    for (x = h, p = NULL; x != NULL; p = x, x = x->next){
        if (KEYcompare(KEYget(x->item), k) == 0){
            if (p == NULL){
                h = x->next;
            } else {
                p->next = x->next;
            }
            free(x);
            return h;
        }
        if (KEYcompare(KEYget(x->item), k) > 0){
            break;
        }
    }
    return h;
}

void LISTshow(link h){
    // funzione che stampa tutti gli elementi della lista
    for (link x = h; x != NULL; x = x->next){
        ITEMshow(x->item);
    }
}