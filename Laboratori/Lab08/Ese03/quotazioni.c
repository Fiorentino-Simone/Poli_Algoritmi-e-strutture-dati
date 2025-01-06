#include "quotazioni.h"

// DEFINIZIONE: per BST ADT di prima classe
typedef struct BSTnode *link;
struct BSTnode
{
    Quotazione item;
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

// FUNCTIONS
static link NEW(Quotazione item, link p, link l, link r, int N)
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
    bst->root = (bst->z = NEW(QuotazionesetNull(), NULL, NULL, NULL, 0));
    return bst;
}

Quotazione QuotazionesetNull()
{
    Quotazione val;
    val.data.YYYY = val.data.MM = val.data.DD = 0;
    val.data.hh = val.data.mm = 0;

    val.valore = 0;
    val.quantita = 0;
    return val;
}

static void freeR(link h, link z)
{
    if (h == z)
        return;
    freeR(h->l, z);
    freeR(h->r, z);
    free(h);
}

void BSTfree(BST bst)
{
    freeR(bst->root, bst->z);
}

BST BSTreadFile(FILE *fp, BST bst)
{
    Quotazione val;
    int nTransazioni;

    fscanf(fp, "%d", &nTransazioni);
    for (int i = 0; i < nTransazioni; i++)
    {
        val = QuotazioneScan(fp);
        BSTinsert_leafR(bst, val);
    }
    return bst;
}

Quotazione QuotazioneScan(FILE *fp)
{
    Quotazione val;
    fscanf(fp, "%d/%d/%d %d:%d %f %d", &val.data.YYYY, &val.data.MM, &val.data.DD, &val.data.hh, &val.data.mm, &val.valore, &val.quantita);
    return val;
}

static Datetime DatetimeScan(FILE *fp)
{
    Datetime data;
    fscanf(fp, "%d/%d/%d %d:%d", &data.YYYY, &data.MM, &data.DD, &data.hh, &data.mm);
    return data;
}

static Quotazione searchR(link h, Quotazione k, link z)
{
    int cmp;
    if (h == z)
    {
        printf("Quotazione non trovata!\n");
        return QuotazionesetNull();
    }
    cmp = KEYcmp(KEYget(k.data), KEYget(h->item.data));
    if (cmp == 0)
    {
        return h->item;
    }
    if (cmp == -1)
        return searchR(h->l, k, z);
    else
        return searchR(h->r, k, z);
}

Quotazione BSTsearch(BST bst)
{
    Quotazione k;
    printf("Inserisci la data della quotazione da cercare (YYYY/MM/DD hh:mm): ");
    k.data = DatetimeScan(stdin);
    k.valore = 0;
    k.quantita = 0;
    return searchR(bst->root, k, bst->z);
}

Quotazione BSTnodeUpdate(Quotazione item, Quotazione k)
{
    item.valore = (float)(((item.valore * (float)item.quantita) + (k.valore * (float)k.quantita)) / ((float)item.quantita + (float)k.quantita));
    item.quantita += k.quantita;
    return item;
}

static link insertR(link h, Quotazione x, link z)
{
    if (h == z)
        return NEW(x, z, z, z, 1);
    if (KEYcmp(KEYget(x.data), KEYget(h->item.data)) == -1)
    {
        h->l = insertR(h->l, x, z);
        h->l->p = h;
    }
    else if (KEYcmp(KEYget(x.data), KEYget(h->item.data)) == 1)
    {
        h->r = insertR(h->r, x, z);
        h->r->p = h;
    }
    else
    {
        h->item = BSTnodeUpdate(h->item, x);
    }
    h->N++;
    return h;
}

void BSTinsert_leafR(BST bst, Quotazione x)
{
    bst->root = insertR(bst->root, x, bst->z);
}

static void BSTinOrderMinMax(link h, link z, Datetime data1, Datetime data2, Quotazione *min, Quotazione *max)
{
    if (h == z)
        return;
    BSTinOrderMinMax(h->l, z, data1, data2, min, max);
    if (KEYcmp(KEYget(data1), KEYget(h->item.data)) <= 0 && KEYcmp(KEYget(data2), KEYget(h->item.data)) >= 0)
    {
        if (min->valore == 0 || h->item.valore < min->valore)
        {
            *min = h->item;
        }
        if (max->valore == 0 || h->item.valore > max->valore)
        {
            *max = h->item;
        }
    }
    BSTinOrderMinMax(h->r, z, data1, data2, min, max);
}

void searchBSTQuotationMINMAXFromRangeDate(BST bst)
{
    Datetime data1, data2;
    Quotazione min, max;

    min = QuotazionesetNull();
    min.valore = 500000;
    max = QuotazionesetNull();
    
    printf("Inserisci la data di inizio (YYYY/MM/DD hh:mm): ");
    data1 = DatetimeScan(stdin);
    printf("Inserisci la data di fine (YYYY/MM/DD hh:mm): ");
    data2 = DatetimeScan(stdin);
    
    BSTinOrderMinMax(bst->root, bst->z, data1, data2, &min, &max);
    if (min.valore != 0 && max.valore != 0)
    {
        printf("Quotazioni trovate!\n");
        printf("Quotazione minima:\n");
        QuotazioneStore(min);
        printf("Quotazione massima:\n");
        QuotazioneStore(max);
    }
    else
    {
        printf("Nessuna quotazione trovata!\n");
    }
}

static void BSTinOrderMinMaxAllPeriod(link h, link z, Quotazione *min, Quotazione *max)
{
    if (h == z)
        return;
    BSTinOrderMinMaxAllPeriod(h->l, z, min, max);
    if (min->valore == 0 || h->item.valore < min->valore)
    {
        *min = h->item;
    }
    if (max->valore == 0 || h->item.valore > max->valore)
    {
        *max = h->item;
    }
    BSTinOrderMinMaxAllPeriod(h->r, z, min, max);
}

void searchBSTQuotationMINMAXFromAllPeriod(BST bst)
{
    Quotazione min, max;

    min = QuotazionesetNull();
    min.valore = 500000;
    max = QuotazionesetNull();
    
    BSTinOrderMinMaxAllPeriod(bst->root, bst->z, &min, &max);
    if (min.valore != 0 && max.valore != 0)
    {
        printf("Quotazioni trovate!\n");
        printf("Quotazione minima:\n");
        QuotazioneStore(min);
        printf("Quotazione massima:\n");
        QuotazioneStore(max);
    }
    else
    {
        printf("Nessuna quotazione trovata!\n");
    }
}

static link rotR(link h)
{
    link x = h->l;
    h->l = x->r;
    x->r->p = h;
    x->r = h;
    x->p = h->p;
    h->p = x;
    x->N = h->N;
    h->N = (h->l ? h->l->N : 0) + (h->r ? h->r->N : 0) + 1;
    return x;
}

static link rotL(link h)
{
    link x = h->r;
    h->r = x->l;
    x->l->p = h;
    x->l = h;
    x->p = h->p;
    h->p = x;
    x->N = h->N;
    h->N = (h->l ? h->l->N : 0) + (h->r ? h->r->N : 0) + 1;
    return x;
}

static link partR(link h, int r)
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

static int AltezzaAlberoMassima(link h, link z)
{
    if (h == z)
        return -1;
    int l = AltezzaAlberoMassima(h->l, z);
    int r = AltezzaAlberoMassima(h->r, z);
    return 1 + (l > r ? l : r);
}

int AltezzaAlberoMassimaWrapper(BST bst)
{
    return AltezzaAlberoMassima(bst->root, bst->z);
}

static int AltezzaAlberoMinima(link h, link z)
{
    if (h == z)
        return -1;
    int l = AltezzaAlberoMinima(h->l, z);
    int r = AltezzaAlberoMinima(h->r, z);
    return 1 + (l < r ? l : r);
}

int AltezzaAlberoMinimaWrapper(BST bst)
{
    return AltezzaAlberoMinima(bst->root, bst->z);
}

void BSTbalance(BST bst)
{
    // bilanciamento dell'albero di quotazioni se il rapporto tra il cammino più lungo e più corto nell'albero supera una certa soglia S.
    int max = AltezzaAlberoMassimaWrapper(bst);
    int min = AltezzaAlberoMinimaWrapper(bst);
    float rapporto = (float)max / (float)min;
    if (rapporto > 2)
    {
        printf("Bilanciamento necessario!\n");
        bst->root = balanceR(bst->root, bst->z);
    }
    else
    {
        printf("Bilanciamento non necessario!\n");
    }
}

// PRINT
void QuotazioneStore(Quotazione val)
{
    printf("%d/%d/%d %d:%d %f %d\n", val.data.YYYY, val.data.MM, val.data.DD, val.data.hh, val.data.mm, val.valore, val.quantita);
}

static void treePrintR(link h, link z)
{
    if (h == z)
        return;
    treePrintR(h->l, z);
    QuotazioneStore(h->item);
    treePrintR(h->r, z);
}

void BSTprint(BST bstq)
{
    treePrintR(bstq->root, bstq->z);
}
