#ifndef ESE03_PERSONAGGI_H
#define ESE03_PERSONAGGI_H

#include "inventario.h"
#include <stdlib.h>
#include <stdio.h>

// DEFINE
#define MAXN 50
#define MAXNEQUIP 8
#define MAXCODE 7

// TYPEDEF
typedef struct
{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
} stat_t;

typedef struct
{
    int inUso;
    inv_t vettEq[MAXNEQUIP];
} tabEquip_t;

typedef struct
{
    char codice[MAXCODE];
    char nome[MAXN];
    char classe[MAXN];
    tabEquip_t equip;
    stat_t stat_base; // Valori delle statistiche inserite all'inizio
    stat_t stat;     // Valori delle statistiche quando calcolate
} Pg_t;

typedef struct nodoPg *nodePg_t;
typedef struct
{
    Pg_t val;
    nodePg_t next;
} nodoPg;

typedef struct
{
    nodoPg *headPg, *tailPg;
    int nPg;
} tabPg_t;

// PROTOTIPI
tabPg_t *initPersonaggi();
tabPg_t *leggiPersonaggi(tabPg_t *tabPg);

void inserimento_in_coda_personaggio(tabPg_t *tabPg, Pg_t personaggi);
void stampaPersonaggi(tabPg_t *tabPg);
void stampaPersonaggio(Pg_t personaggio);
void stampaEquipaggiamento(nodoPg *nodo, int i);

tabPg_t *aggiungiPersonaggio(tabPg_t *tabPg);
void rimuoviPersonaggio(tabPg_t *tabPg);
nodoPg *ricerca_codice(nodoPg *lista, char *cod);
nodoPg *elimina_codice(nodoPg *lista, nodoPg **coda, nodoPg *temp);

void aggiungiOggetto(tabPg_t *tabPg, tabInv_t *tabI);
void rimuoviOggetto(tabPg_t *tabPg, tabInv_t *tabI);

void calcolaStatistiche(tabPg_t *tabPg, tabInv_t *tabI);

void freePersonaggi(tabPg_t *tabPg);

#endif // ESE03_PERSONAGGI_H
