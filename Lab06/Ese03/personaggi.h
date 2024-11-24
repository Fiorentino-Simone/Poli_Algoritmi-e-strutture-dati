#ifndef ESE03_PERSONAGGI_H
#define ESE03_PERSONAGGI_H

#include "inventario.h"
#include <stdlib.h>
#include <stdio.h>

// DEFINE
#define MAXN 50
#define MAXNEQUIP 8

// TYPEDEF
typedef struct{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
} stat_t;

typedef struct{
    int inUso;
    inv_t vettEq[MAXNEQUIP];
} tabEquip_t;

typedef struct{
    char codice[MAXN];
    char nome[MAXN];
    char classe[MAXN];
    tabEquip_t equip;
    stat_t stat;
} Pg_t;

typedef struct nodoPg *nodePg_t;
typedef struct{
    Pg_t val;
    nodePg_t next;
} nodoPg;

typedef struct {
    nodoPg *headPg, *tailPg;
    int nPg;
} tabPg_t;

// PROTOTIPI
tabPg_t* leggiPersonaggi(tabPg_t *tabPg);
tabPg_t *inizializzazionePersonaggi();
void inserimento_in_testa_personaggio(tabPg_t *tabPg, Pg_t personaggi);
void stampaPersonaggi(tabPg_t *tabp);
void stampaequippagiamentopersonaggio(nodoPg *nodo,int i);

#endif //ESE03_PERSONAGGI_H
