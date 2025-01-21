#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "BST.h"

typedef struct node *link;

struct node{
    link l;
    link r;
    Menu menu;
};

struct tree{
    link radice;
    link z;
};

static Menu MENUsetNull(){
    Menu m;
    m.elencoPortate=NULL;
    m.costoTotale=0;
    return m;
}

int MENUcompare(Menu menu1, Menu menu2, int P){
    int cmp;
    if(menu1.costoTotale < menu2.costoTotale){
        return -1;
    } else if(menu1.costoTotale > menu2.costoTotale){
        return 1;
    } else {
        // prezzo uguale controllo i piatti
        for (int i = 0; i < P; i++) {
            cmp = strcmp(menu1.elencoPortate[i].nome, menu2.elencoPortate[i].nome);
            if(cmp == 0) continue;
            else return cmp;
        }
    }
    return 0;
}

static void MENUprint(Menu m, int P){
    for (int i = 0; i < P; i++) {
        printf("%s %s %s %.2f\n", m.elencoPortate[i].nome, m.elencoPortate[i].portata, m.elencoPortate[i].tipologia, m.elencoPortate[i].costo);
    }
    printf("Costo totale: %.2f", m.costoTotale);
    printf("\n");
}

static link NEWnode(link l, link r, Menu menu){
    link x = malloc(sizeof(*x));
    x->l = l;
    x->r = r;
    x->menu = menu;
    return x;
}

BST BSTinit(){
    BST bst = malloc(sizeof(*bst));
    bst->radice = (bst->z = NEWnode(NULL, NULL, MENUsetNull()));
    return bst;
}

static void treeFreeR(link head, link z){
    if(head==z)
        return;
    treeFreeR(head->l, z);
    treeFreeR(head->r, z);
    free(head);
}

void BSTfree(BST bst){
    if(bst!=NULL){
        treeFreeR(bst->radice, bst->z);
        free(bst->z);
        free(bst);
    }
}

static link BSTinsertLeafR(link h, link z, Menu menu, int P){
    if(h == z){
        return NEWnode(z, z , menu);
    }
    if(MENUcompare(menu, h->menu, P) == -1){
        h->l = BSTinsertLeafR(h->l, z, menu, P);
    }
    else if(MENUcompare(menu, h->menu, P) == 1){
        h->r = BSTinsertLeafR(h->r, z, menu, P);
    }
    return h;
}

void BSTinsertLeaf(BST bst, Menu menu, int P){
    bst->radice = BSTinsertLeafR(bst->radice, bst->z, menu, P);
}

static void BSTprintR(link h, link z, int P){
    if(h == z){
        return;
    }

    BSTprintR(h->l, z, P);
    MENUprint(h->menu, P);
    printf("\n");
    BSTprintR(h->r, z, P);
}

void BSTprint(BST bst, int P){
    BSTprintR(bst->radice, bst->z, P);
}