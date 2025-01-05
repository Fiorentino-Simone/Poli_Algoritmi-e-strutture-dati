#include "equipArray.h"

/* Dichiaro l'ADT di prima classe */
struct equipArray_s
{
    int *vettEq;
    int inUso, max_n;
};

equipArray_t equipArray_init()
{
    equipArray_t equipArray = malloc(sizeof(struct equipArray_s));
    equipArray->inUso = 0;
    equipArray->max_n = EQUIP_SLOT;

    // possibile fare riallocazione se necessario aggiugere altri elementi
    equipArray->vettEq = malloc(EQUIP_SLOT * sizeof(int));

    if (equipArray->vettEq == NULL)
    {
        fprintf(stderr, "Errore allocazione dinamica.\n");
        exit(1);
    }

    return equipArray;
}

void equipArray_free(equipArray_t equipArray)
{
    if (equipArray != NULL)
    {
        if (equipArray->vettEq != NULL)
            free(equipArray->vettEq);

        free(equipArray);
    }
}

int equipArray_inUse(equipArray_t equipArray)
{
    return equipArray->inUso;
}

void equipArray_print(FILE *fp, equipArray_t equipArray, invArray_t invArray)
{
    int i;
    if (equipArray->inUso == 0)
    {
        return;
    }

    fprintf(fp, "\nEquipaggiamenti:\n");
    for (i = 0; i < equipArray->inUso; i++)
    {
        invArray_printByIndex(fp, invArray, equipArray->vettEq[i]);
        printf("\n");
    }
}

void equipArray_update(equipArray_t equipArray, invArray_t invArray)
{
    int i;
    if (equipArray->inUso >= equipArray->max_n)
    {
        printf("Hai superato il numero massimo di oggetti implementabili!");
        return;
    }

    printf("Equipaggiamenti disponibili:\n");
    invArray_print(stdout, invArray);

    printf("Inserisci l'indice dell'equipaggiamento da aggiungere: ");
    scanf("%d", &i);
    equipArray->vettEq[equipArray->inUso++] = i;
}

int equipArray_getEquipByIndex(equipArray_t equipArray, int index)
{
    if (index >= equipArray->inUso)
    {
        printf("Equipaggio non presente!");
        return -1;
    }
    return equipArray->vettEq[index];
}

stat_t equipArray_getLastStat(equipArray_t equip, invArray_t invArray)
{
    return invArray_getByIndex(invArray, equip->vettEq[equip->inUso - 1])->stat;
}