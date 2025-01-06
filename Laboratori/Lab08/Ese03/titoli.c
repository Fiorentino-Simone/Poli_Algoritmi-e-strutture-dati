#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "titoli.h"

// DEFINIZIONE: struttura dati per il titolo
struct titolo
{
    char name[MAXC];
    BST quotazioni;
};

// DEFINIZIONE: struttura dati per la collezione di titoli (lista ordinata)
typedef struct node *link;
struct node
{
    Titolo val;
    link next;
};
struct listTitolo
{
    link head;
    int N;
};

// FUNCTIONS
LISTtitolo LISTinit()
{
    LISTtitolo l = (LISTtitolo)malloc(sizeof(*l));
    l->head = NULL;
    l->N = 0;
    return l;
}

void LISTfree(LISTtitolo l)
{
    link x, t, temp;
    for (x = l->head; x != NULL; x = t)
    {
        temp = x;
        t = x->next;
        BSTfree(temp->val->quotazioni);
        free(temp);
    }
    free(l);
}

static link NEW(Titolo val, link next)
{
    link x = malloc(sizeof(*x));
    x->val = val;
    x->next = next;
    return x;
}

static link LISTinsertSort(LISTtitolo l, char *name, FILE *fp)
{
    link x, p;

    Titolo t = malloc(sizeof(*t));
    strcpy(t->name, name);
    t->quotazioni = BSTinit();

    x = l->head;
    p = NULL;
    while (x != NULL && strcmp(x->val->name, name) < 0)
    {
        p = x;
        x = x->next;
    }
    if (p == NULL)
    {
        l->head = NEW(t, l->head);
    }
    else
    {
        p->next = NEW(t, x);
    }
    t->quotazioni = BSTreadFile(fp, t->quotazioni);
    l->N++;
    return l->head;
}

LISTtitolo readfile(FILE *fp, LISTtitolo l)
{
    char name[MAXC];
    int n;

    fscanf(fp, "%d", &n);
    for (int i = 0; i < n; i++)
    {
        fscanf(fp, "%s", name);
        l->head = LISTinsertSort(l, name, fp);
    }
    LISTprint(l);
    return l;
}

void LISTprint(LISTtitolo l)
{
    link x;
    for (x = l->head; x != NULL; x = x->next)
    {
        printf("%s\n", x->val->name);
        BSTprint(x->val->quotazioni);
    }
    if (l->N == 0)
    {
        printf("Lista vuota!\n");
    }
}

void searchTitle(LISTtitolo l)
{
    char name[MAXC];
    link x;
    printf("Inserisci il nome del titolo: ");
    scanf("%s", name);
    for (x = l->head; x != NULL; x = x->next)
    {
        if (strcmp(x->val->name, name) == 0)
        {
            printf("Titolo trovato!\n");
            BSTprint(x->val->quotazioni);
            return;
        }
    }
    printf("Titolo non trovato!\n");
}

void searchQuotation(LISTtitolo l)
{
    // ricerca quotazione da una certa data (BSTsearch)
    char name[MAXC];
    link x;
    Quotazione q;

    printf("Inserisci il nome del titolo: ");
    scanf("%s", name);
    for (x = l->head; x != NULL; x = x->next)
    {
        if (strcmp(x->val->name, name) == 0)
        {
            printf("Titolo trovato!\n");
            q = BSTsearch(x->val->quotazioni);
            if (q.valore != 0)
            {
                printf("Quotazione trovata!\n");
                QuotazioneStore(q);
            }
            return;
        }
    }
    printf("Titolo non trovato!\n");
}

void searchQuotationMinMax(LISTtitolo l)
{
    // ricerca quotazione minima e massima da una certa data a un'altra (searchBSTQuotationMINMAXFromRangeDate)
    char name[MAXC];
    link x;

    printf("Inserisci il nome del titolo: ");
    scanf("%s", name);
    for (x = l->head; x != NULL; x = x->next)
    {
        if (strcmp(x->val->name, name) == 0)
        {
            printf("Titolo trovato!\n");
            searchBSTQuotationMINMAXFromRangeDate(x->val->quotazioni);
            return;
        }
    }
    printf("Titolo non trovato!\n");
}

void searchQuotationMinMaxAllPeriod(LISTtitolo l)
{
    // ricerca quotazione minima e massima di tutto il periodo (searchBSTQuotationMINMAXFromAllPeriod)
    char name[MAXC];
    link x;

    printf("Inserisci il nome del titolo: ");
    scanf("%s", name);
    for (x = l->head; x != NULL; x = x->next)
    {
        if (strcmp(x->val->name, name) == 0)
        {
            printf("Titolo trovato!\n");
            searchBSTQuotationMINMAXFromAllPeriod(x->val->quotazioni);
            return;
        }
    }
    printf("Titolo non trovato!\n");
}

void balanceTree(LISTtitolo l)
{
    char name[MAXC];
    link x;

    printf("Inserisci il nome del titolo: ");
    scanf("%s", name);
    for (x = l->head; x != NULL; x = x->next)
    {
        if (strcmp(x->val->name, name) == 0)
        {
            printf("Titolo trovato!\n");
            BSTbalance(x->val->quotazioni);
            return;
        }
    }
    printf("Titolo non trovato!\n");
}