#include "BST.h"

typedef struct BSTnode* link;
struct BSTnode { Item item; link p; link l; link r; int N; };
struct binarysearchtree { link root; link z; };

static link NEW(Item item, link p, link l, link r, int N) {
    link x = malloc(sizeof *x);
    x->item = item;
    x->p = p;
    x->l = l;
    x->r = r;
    x->N = N;
    return x;
}

BST BSTinit() {
    BST bst = malloc(sizeof *bst);
    bst->root = (bst->z = NEW(ITEMsetNull(), NULL, NULL, NULL, 0));
    return bst;
}

static void BSTfreeR(link h, link z) {
    if (h == z){
        return;
    }
    treeFree(h->l, z);
    treeFree(h->r, z);
    free(h);
}

void BSTfree(BST bst) {
    link x = bst->root;
    if (x != bst->z) {
        BSTfreeR(x->l, bst->z);
        BSTfreeR(x->r, bst->z);
    }
    free(bst->z);
    free(bst);
}

static int countR(link h, link z) {
    if (h == z) {
        return 0;
    }
    return countR(h->l, z) + countR(h->r, z) + 1;
}

int BSTcount(BST bst){
    return countR(bst->root, bst->z);
}

int BSTempty(BST bst){
    return bst->root == bst->z; // oppure BSTcount(bst) == 0 (P.S: 1 se vuoto, 0 se pieno)
}

static Item searchR(link h, Key k, link z) {
    int cmp;    
    if (h == z) {
        return ITEMsetNull();
    }

    cmp = KEYcompare(k, KEYget(h->item));
    if (cmp == 0) {
        return h->item;
    }
    if (cmp == -1) {
        return searchR(h->l, k, z);
    } else {
        return searchR(h->r, k, z);
    }
}

Item BSTsearch(BST bst, Key k){
    return searchR(bst->root, k, bst->z);
}

static Item minR(link h, link z) {
    if (h == z) {
        return ITEMsetNull();
    }
    if (h->l == z) {
        return h->item; // si continua a cercare a sinistra finchè non si trova il minimo
    }
    return minR(h->l, z);
}

Item BSTmin(BST bst){
    return minR(bst->root, bst->z);
}

static Item maxR(link h, link z) {
    if (h == z) {
        return ITEMsetNull();
    }
    if (h->r == z) {
        return h->item; // si continua a cercare a destra finchè non si trova il massimo
    }
    return maxR(h->r, z);
}

Item BSTmax(BST bst){
    return maxR(bst->root, bst->z);
}

static link insertR(link h, Item x, link z) {
    int cmp;
    if (h == z) {
        return NEW(x, z, z, z, 1);
    }
    cmp = KEYcompare(KEYget(x), KEYget(h->item));
    if (cmp == -1) {
        h->l = insertR(h->l, x, z);
        h->l->p = h; // deve essere aggiornato il puntatore al padre per il figlio sinistro
    } else {
        h->r = insertR(h->r, x, z);
        h->r->p = h; // deve essere aggiornato il puntatore al padre per il figlio destro
    }
    (h->N)++;
    return h;
}

void BSTinsert_leafR(BST bst, Item x){
    // inserimento in foglia ricorsivo, aggiornando il puntatore alla radice
    bst->root = insertR(bst->root, x, bst->z);
}

void BSTinsert_leafI(BST bst, Item x){
    // inserimento in foglia iterativo
    link p = bst->root;
    link h = bst->root;

    if (bst->root == bst->z) {
        bst->root = NEW(x, bst->z, bst->z, bst->z, 1);
        return;
    }

    // trovo la posizione in cui inserire l'elemento
    while (h != bst->z) {
        p = h;
        if (KEYcompare(KEYget(x), KEYget(h->item)) == -1) {
            h = h->l;
        } else {
            h = h->r;
        }
    }
    h = NEW(x, p, bst->z, bst->z, 1);
    if (KEYcompare(KEYget(x), KEYget(p->item)) == -1) {
        p->l = h;
    } else {
        p->r = h;
    }
}

static link rotL(link h) {
    link x = h->r;
    h->r = x->l;
    x->l = h;
    return x;
}

static link rotR(link h) {
    link x = h->l;
    h->l = x->r;
    x->r = h;
    return x;
}

static link insertT(link h, Item x, link z) {
    int cmp;
    if (h == z) {
        return NEW(x, z, z);
    }
    cmp = KEYcompare(KEYget(x), KEYget(h->item));
    if (cmp == -1) {
        h->l = insertT(h->l, x, z);
        h = rotR(h);
    } else {
        h->r = insertT(h->r, x, z);
        h = rotL(h);
    }
    return h;
}

void BSTinsert_root(BST bst, Item x){
    // inserimento in radice (uso le rotazioni)
    bst->root = insertT(bst->root, x, bst->z);
}