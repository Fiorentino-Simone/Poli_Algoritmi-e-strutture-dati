#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "st.h"

// DEFINIZIONE SYMBOLTABLE
struct symboltable
{
    char **names;
    char **subnets;
    int maxN;
    int N;
};

// FUNCTIONS
ST STinit(int maxN)
{
    ST st;
    st = malloc(sizeof(*st));
    if (st == NULL)
    {
        printf("Errore nell'allocazione!");
        exit(-1);
    }

    st->names = malloc(maxN * sizeof(char *));
    if (st->names == NULL)
    {
        printf("Errore nell'allocazione!");
        exit(-1);
    }

    st->subnets = malloc(maxN * sizeof(char *));
    if (st->subnets == NULL)
    {
        printf("Errore nell'allocazione!");
        exit(-1);
    }

    st->maxN = maxN;
    st->N = 0;
    return st;
}

void STfree(ST st)
{
    for (int i = 0; i < st->N; i++)
    {
        free(st->names[i]);
        free(st->subnets[i]);
    }
    free(st->names);
    free(st->subnets);
    free(st);
}

int STcount(ST st)
{
    return st->N;
}

int STsearch(ST st, char *name)
{
    for (int i = 0; i < st->N; i++)
    {
        if (strcmp(st->names[i], name) == 0)
        {
            return i;
        }
    }
    return -1;
}

void STinsert(ST st, char *name, char *subnet)
{
    if (st->N == st->maxN)
    {
        printf("Symbol table piena!");
        exit(-1);
    }

    st->names[st->N] = malloc(strlen(name) + 1);
    strcpy(st->names[st->N], name);

    st->subnets[st->N] = malloc(strlen(subnet) + 1);
    strcpy(st->subnets[st->N], subnet);

    st->N++;
}

char *STsearchByIndexName(ST st, int index)
{
    return st->names[index];
}

char *STsearchByIndexSubnet(ST st, int index)
{
    return st->subnets[index];
}

int STsearchByName(ST st, char *name)
{
    for (int i = 0; i < st->N; i++)
    {
        if (strcmp(st->names[i], name) == 0)
        {
            return i;
        }
    }
    return -1;
}

void STsort(ST st, int *a)
{
    int temp;
    for (int i = 0; i < st->N; i++)
    {
        a[i] = i;
    }

    for (int i = 0; i < st->N - 1; i++)
    {
        for (int j = 0; j < st->N - 1 - i; j++)
        {
            if (strcmp(st->names[a[j + 1]], st->names[a[j]]) < 0)
            {
                temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }
}