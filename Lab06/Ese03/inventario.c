#include "inventario.h"
#include <stdio.h>
#include <stdlib.h>

tabInv_t *leggiInventario()
{
    FILE *fin;
    tabInv_t *tabI;

    tabI = (tabInv_t *)malloc(sizeof(*tabI));

    /*char filename[MAXN];

    printf("Inserisci nome del file per l'aggiunta dell'inventario: ");
    scanf("%s", filename);*/

    fin = fopen("inventario.txt", "r");
    if (fin == NULL)
    {
        printf("Errore nella lettura del file!");
        exit(1);
    }

    fscanf(fin, "%d", &tabI->nInv);
    tabI->vettInv = (inv_t *)malloc((tabI->nInv) * sizeof(inv_t));
    tabI->maxInv = tabI->nInv;

    for (int i = 0; i < tabI->nInv; ++i)
    {
        fscanf(fin, "%s %s %d %d %d %d %d %d",
                tabI->vettInv[i].nome,
                tabI->vettInv[i].tipo,
                &(tabI->vettInv[i].stat.hp),
                &(tabI->vettInv[i].stat.mp),
                &(tabI->vettInv[i].stat.atk),
                &(tabI->vettInv[i].stat.def),
                &(tabI->vettInv[i].stat.mag),
                &(tabI->vettInv[i].stat.spr));
    }

    fclose(fin);
    return tabI;
}

void stampaInventario(tabInv_t *tabI)
{
    for (int i = 0; i < tabI->nInv; ++i)
    {
        stampaOggetto(tabI->vettInv[i]);
    }
    printf("Numero Oggetti: %d\n", tabI->nInv);
    printf("\n");
}

void stampaOggetto(inv_t oggetto)
{
    printf("%s %s %d %d %d %d %d %d",
            oggetto.nome,
            oggetto.tipo,
            oggetto.stat.hp,
            oggetto.stat.mp,
            oggetto.stat.atk,
            oggetto.stat.def,
            oggetto.stat.mag,
            oggetto.stat.spr);
    printf("\n");
}

int ricerca_oggetto(tabInv_t *tabI, char *nome)
{
    for (int i = 0; i < tabI->nInv; ++i)
    {
        if (strcmp(tabI->vettInv[i].nome, nome) == 0)
        {
            return i;
        }
    }
    return -1;
}