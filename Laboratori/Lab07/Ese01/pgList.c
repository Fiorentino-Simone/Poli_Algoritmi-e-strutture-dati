#include "pgList.h"

/* Dichiarazione dell'ADT di prima classe come lista concatenata */
typedef struct nodoPg *nodePg_t;
typedef struct
{
    pg_t val;
    nodePg_t next;
} nodoPg;

struct pgList_s
{
    nodoPg *headPg;
    int nPg;
};

pgList_t pgList_init()
{
    pgList_t lista = malloc(sizeof(*lista));
    lista->headPg = NULL;
    lista->nPg = 0;
    return lista;
}

void pgList_read(FILE *fp, pgList_t pgList)
{
    pg_t pgNew;
    while (pg_read(fp, &(pgNew)) == 1)
    {
        pgList_insert(pgList, pgNew);
    }
}

void pgList_insert(pgList_t pgList, pg_t pg)
{
    nodoPg *new_node = malloc(sizeof(*new_node));
    if (new_node == NULL)
    {
        printf("Errore nell'allocazione!");
        return;
    }

    new_node->val = pg;
    new_node->next = pgList->headPg;
    pgList->headPg = new_node;
    pgList->nPg++;
}

void pgList_print(FILE *fp, pgList_t pgList, invArray_t invArray)
{
    nodoPg *nodo;

    nodo = pgList->headPg;
    printf("\n");
    while (nodo != NULL)
    {
        pg_print(fp, &(nodo->val), invArray);
        nodo = nodo->next;
    }
    fprintf(fp, "Numero personaggi: %d\n\n", pgList->nPg);
}

pg_t *pgList_searchByCode(pgList_t pgList, char *cod)
{
    nodoPg *lista = pgList->headPg;
    while (lista != NULL)
    {
        if (strcmp(lista->val.cod, cod) == 0)
        {
            return &(lista->val);
        }
        lista = lista->next;
    }
    return NULL;
}

void pgList_free(pgList_t pgList)
{
    nodoPg *temp;

    while (pgList->headPg != NULL)
    {
        temp = pgList->headPg;
        pgList->headPg = pgList->headPg->next;
        free(temp);
    }
    free(pgList);
}

void pgList_remove(pgList_t pgList, char *cod)
{
    nodoPg *p, *x;

    // se l'elemento è in testa bisogna cancellare e modificare ciò a cui punta
    if (strcmp(pgList->headPg->val.cod, cod) == 0)
    {
        pg_print(stdout, &(pgList->headPg->val), NULL);
        pg_clean(&(pgList->headPg->val));
        x = pgList->headPg;
        free(x);
        if (pgList->headPg != NULL)
        {
            pgList->headPg = pgList->headPg->next;
        }
        pgList->nPg--;
        return;
    }

    for (p = pgList->headPg; p != NULL; x = p, p = p->next)
    {
        if (strcmp(p->val.cod, cod) == 0)
        {
            pg_print(stdout, &(p->val), NULL);
            x->next = p->next;
            pg_clean(&(p->val));
            free(p);
            pgList->nPg--;
            return;
        }
    }
    fprintf(stdout, "Personaggio non trovato.\n");
}