#ifndef ESE03_INVENTARIO_H
#define ESE03_INVENTARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// DEFINE
#define MAXN 50

typedef struct
{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
} stat_t0;

typedef struct
{
    char nome[MAXN];
    char tipo[MAXN];
    stat_t0 stat;
} inv_t;

typedef struct
{
    inv_t *vettInv;
    int nInv, maxInv;
} tabInv_t;

// PROTOTIPI
tabInv_t *leggiInventario();

void stampaInventario(tabInv_t *tabI);
void stampaOggetto(inv_t oggetto);

int ricerca_oggetto(tabInv_t *tabI, char *nome);

#endif // ESE03_INVENTARIO_H
