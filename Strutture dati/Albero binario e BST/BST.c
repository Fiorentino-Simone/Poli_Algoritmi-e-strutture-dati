#include "BST.h"

typedef struct BSTnode *link;

struct BSTnode
{
    Item item;
    link p;
    link l;
    link r;
    int N;
};

struct binarysearchtree
{
    link root;
    link z;
};

typedef enum {PREORDER, INORDER, POSTORDER} Strategy;

static link NEW(Item item, link p, link l, link r, int N)
{
    link x = malloc(sizeof *x);
    x->item = item;
    x->p = p;
    x->l = l;
    x->r = r;
    x->N = N;
    return x;
}

BST BSTinit()
{
    BST bst = malloc(sizeof *bst);
    bst->root = (bst->z = NEW(ITEMsetNull(), NULL, NULL, NULL, 0));
    return bst;
}

static void BSTfreeR(link h, link z)
{
    if (h == z)
    {
        return;
    }
    treeFree(h->l, z);
    treeFree(h->r, z);
    free(h);
}

void BSTfree(BST bst)
{
    link x = bst->root;
    if (x != bst->z)
    {
        BSTfreeR(x->l, bst->z);
        BSTfreeR(x->r, bst->z);
    }
    free(bst->z);
    free(bst);
}

static int countR(link h, link z)
{
    if (h == z)
    {
        return 0;
    }
    return countR(h->l, z) + countR(h->r, z) + 1;
}

int BSTcount(BST bst)
{
    return countR(bst->root, bst->z);
}

int BSTempty(BST bst)
{
    return bst->root == bst->z; // oppure BSTcount(bst) == 0 (P.S: 1 se vuoto, 0 se pieno)
}

static Item searchR(link h, Key k, link z)
{
    int cmp;
    if (h == z)
    {
        return ITEMsetNull();
    }

    cmp = KEYcompare(k, KEYget(h->item));
    if (cmp == 0)
    {
        return h->item;
    }
    if (cmp == -1)
    {
        return searchR(h->l, k, z);
    }
    else
    {
        return searchR(h->r, k, z);
    }
}

Item BSTsearch(BST bst, Key k)
{
    return searchR(bst->root, k, bst->z);
}

static Item minR(link h, link z)
{
    if (h == z)
    {
        return ITEMsetNull();
    }
    if (h->l == z)
    {
        return h->item; // si continua a cercare a sinistra finchè non si trova il minimo
    }
    return minR(h->l, z);
}

Item BSTmin(BST bst)
{
    return minR(bst->root, bst->z);
}

static Item maxR(link h, link z)
{
    if (h == z)
    {
        return ITEMsetNull();
    }
    if (h->r == z)
    {
        return h->item; // si continua a cercare a destra finchè non si trova il massimo
    }
    return maxR(h->r, z);
}

Item BSTmax(BST bst)
{
    return maxR(bst->root, bst->z);
}

static link insertR(link h, Item x, link z)
{
    int cmp;
    if (h == z)
    {
        return NEW(x, z, z, z, 1);
    }
    cmp = KEYcompare(KEYget(x), KEYget(h->item));
    if (cmp == -1)
    {
        h->l = insertR(h->l, x, z);
        h->l->p = h; // deve essere aggiornato il puntatore al padre per il figlio sinistro
    }
    else
    {
        h->r = insertR(h->r, x, z);
        h->r->p = h; // deve essere aggiornato il puntatore al padre per il figlio destro
    }
    (h->N)++;
    return h;
}

void BSTinsert_leafR(BST bst, Item x)
{
    // inserimento in foglia ricorsivo, aggiornando il puntatore alla radice
    bst->root = insertR(bst->root, x, bst->z);
}

void BSTinsert_leafI(BST bst, Item x)
{
    // inserimento in foglia iterativo
    link p = bst->root;
    link h = bst->root;

    if (bst->root == bst->z)
    {
        bst->root = NEW(x, bst->z, bst->z, bst->z, 1);
        return;
    }

    // trovo la posizione in cui inserire l'elemento
    while (h != bst->z)
    {
        p = h;
        if (KEYcompare(KEYget(x), KEYget(h->item)) == -1)
        {
            h = h->l;
        }
        else
        {
            h = h->r;
        }
    }
    h = NEW(x, p, bst->z, bst->z, 1);
    if (KEYcompare(KEYget(x), KEYget(p->item)) == -1)
    {
        p->l = h;
    }
    else
    {
        p->r = h;
    }
}

link rotL(link h)
{
    link x = h->r;
    h->r = x->l;
    x->l->p = h;
    x->l = h;
    x->p = h->p;
    h->p = x;
    x->N = h->N;
    h->N = 1;
    h->N += (h->l) ? h->l->N : 0;
    h->N += (h->r) ? h->r->N : 0;
    return x;
}

link rotR(link h)
{
    link x = h->l;
    h->l = x->r;
    x->r->p = h;
    x->r = h;
    x->p = h->p;
    h->p = x;
    x->N = h->N;
    h->N = 1;
    h->N += (h->l) ? h->l->N : 0;
    h->N += (h->r) ? h->r->N : 0;
    return x;
}

static link insertT(link h, Item x, link z)
{
    int cmp;
    if (h == z)
    {
        return NEW(x, z, z, z, 1);
    }
    cmp = KEYcompare(KEYget(x), KEYget(h->item));
    if (cmp == -1)
    {
        h->l = insertT(h->l, x, z);
        h = rotR(h);
        h->N++;
    }
    else
    {
        h->r = insertT(h->r, x, z);
        h = rotL(h);
        h->N++;
    }
    return h;
}

void BSTinsert_root(BST bst, Item x)
{
    // inserimento in radice (uso le rotazioni)
    bst->root = insertT(bst->root, x, bst->z);
}

static Item searchSucc(link h, Key k, link z)
{
    link p;
    if (h == z)
        return ITEMsetNull();
    if (KEYcmp(k, KEYget(h->item)) == 0)
    {
        if (h->r != z)
            return minR(h->r, z);
        else
        {
            p = h->p;
            while (p != z && h == p->r)
            {
                h = p;
                p = p->p;
            }
            return p->item;
        }
    }
    if (KEYcmp(k, KEYget(h->item)) == -1)
        return searchSucc(h->l, k, z);
    return searchSucc(h->r, k, z);
}

Item BSTsucc(BST bst, Key k)
{
    return searchSucc(bst->root, k, bst->z);
}

static Item searchPred(link h, Key k, link z)
{
    link p;
    if (h == z)
        return ITEMsetNull();
    if (KEYcmp(k, KEYget(h->item)) == 0)
    {
        if (h->l != z)
            return maxR(h->l, z);
        else
        {
            p = h->p;
            while (p != z && h == p->l)
            {
                h = p;
                p = p->p;
            }
            return p->item;
        }
    }
    if (KEYcmp(k, KEYget(h->item)) == -1)
        return searchPred(h->l, k, z);
    return searchPred(h->r, k, z);
}

Item BSTpred(BST bst, Key k)
{
    return searchPred(bst->root, k, bst->z);
}

static Item selectR(link h, int r, link z)
{
    int t;
    if (h == z)
        return ITEMsetNull();
    t = h->l->N;
    if (t > r)
        return selectR(h->l, r, z);
    if (t < r)
        return selectR(h->r, r - t - 1, z);
    return h->item;
}

Item BSTselect(BST bst, int r)
{
    return selectR(bst->root, r, bst->z);
}

link partR(link h, int r)
{
    int t = h->l->N;
    if (t > r)
    {
        h->l = partR(h->l, r);
        h = rotR(h);
    }
    if (t < r)
    {
        h->r = partR(h->r, r - t - 1);
        h = rotL(h);
    }
    return h;
}

link joinLR(link a, link b, link z)
{
    if (b == z)
        return a;
    b = partR(b, 0);
    b->l = a;
    a->p = b;
    b->N = a->N + b->r->N + 1;
    return b;
}

static link deleteR(link h, Key k, link z)
{
    link y, p;
    if (h == z)
        return z;
    if (KEYcmp(k, KEYget(h->item)) == -1)
        h->l = deleteR(h->l, k, z);
    if (KEYcmp(k, KEYget(h->item)) == 1)
        h->r = deleteR(h->r, k, z);
    (h->N)--;
    if (KEYcmp(k, KEYget(h->item)) == 0)
    {
        y = h;
        p = h->p;
        h = joinLR(h->l, h->r, z);
        h->p = p;
        free(y);
    }
    return h;
}

void BSTdelete(BST bst, Key k)
{
    bst->root = deleteR(bst->root, k, bst->z);
}

static link balanceR(link h, link z)
{
    int r;
    if (h == z)
        return z;
    r = (h->N + 1) / 2 - 1;
    h = partR(h, r);
    h->l = balanceR(h->l, z);
    h->r = balanceR(h->r, z);
    return h;
}

void BSTbalance(BST bst)
{
    bst->root = balanceR(bst->root, bst->z);
}

static void treePrintR(link h, link z, int strategy)
{
    if (h == z)
        return;
    if (strategy == PREORDER)
        ITEMstore(h->item);
    treePrintR(h->l, z, strategy);
    if (strategy == INORDER)
        ITEMstore(h->item);
    treePrintR(h->r, z, strategy);
    if (strategy == POSTORDER)
        ITEMstore(h->item);
}

void BSTvisit(BST bst, int strategy)
{
    if (BSTempty(bst))
        return;
    treePrintR(bst->root, bst->z, strategy);
}