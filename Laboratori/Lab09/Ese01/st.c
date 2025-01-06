#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "st.h"

// DEFINIZIONE SYMBOLTABLE
struct symboltable
{
    char **vertex;
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

    st->vertex = malloc(maxN * sizeof(char *));
    if (st->vertex == NULL)
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
        free(st->vertex[i]);
    }
    free(st->vertex);
    free(st);
}

int STcount(ST st)
{
    return st->N;
}

int STsearch(ST st, char *vertex)
{
    for (int i = 0; i < st->N; i++)
    {
        if (strcmp(st->vertex[i], vertex) == 0)
        {
            return i;
        }
    }
    return -1;
}

void STinsert(ST st, char *vertex, int index)
{
    if (st->N == st->maxN)
    {
        printf("Symbol table piena!");
        exit(-1);
    }

    st->vertex[index] = strdup(vertex);
    st->N++;
}

char *STsearchByIndex(ST st, int index)
{
    return st->vertex[index];
}