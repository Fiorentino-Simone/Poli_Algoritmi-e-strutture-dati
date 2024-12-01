#include <stdio.h>
#include <string.h>
#include "personaggi.h"
#include "inventario.h"

// DEFINE
#define MAXL 30

// TYPEDEF
typedef enum
{
    r_caricaPersonaggi,
    r_caricaOggetti,
    r_aggiungiPersonaggio,
    r_rimuoviPersonaggio,
    r_aggiungiOggetto,
    r_rimuoviOggetto,
    r_calcolaStatistiche,
    r_stampaPersonaggi,
    r_stampaInventario,
    r_fine,
    r_err
} comando_e;

// PROTOTIPI
comando_e leggi_comando();

int main()
{
    // DICHIARAZIONI
    int continua, comando;
    tabPg_t *tabPg;
    tabInv_t *tabI;

    tabI = NULL;
    tabPg = initPersonaggi();
    continua = 1;

    do
    {
        comando = leggi_comando();
        switch (comando)
        {
        case r_caricaPersonaggi:
            tabPg = leggiPersonaggi(tabPg);
            break;
        case r_caricaOggetti:
            tabI = leggiInventario();
            break;
        case r_aggiungiPersonaggio:
            tabPg = aggiungiPersonaggio(tabPg);
            break;
        case r_rimuoviPersonaggio:
            if(tabPg != NULL && tabPg->headPg != NULL){
                rimuoviPersonaggio(tabPg);
            }
            else {
                printf("Devi prima inserire dei personaggi per cancellarli!\n");
            }
            break;
        case r_aggiungiOggetto:
            if ((tabPg != NULL && tabPg->headPg != NULL) && tabI != NULL) {
                aggiungiOggetto(tabPg, tabI);
            } else {
                printf("Controlla di aver inserito prima sia i personaggi che l'inventario!\n");
            }
            break;
        case r_rimuoviOggetto:
            if ((tabPg != NULL && tabPg->headPg != NULL) && tabI != NULL){
                rimuoviOggetto(tabPg, tabI);
            }
            else {
                printf("Controlla di aver inserito prima sia i personaggi che l'inventario!\n");
            }
            break;
        case r_stampaPersonaggi:
            if(tabPg != NULL && tabPg->headPg != NULL){
                stampaPersonaggi(tabPg);
            } else {
                printf("Non sono presenti personaggi!\n");
            }
            break;
        case r_stampaInventario:
            if(tabI != NULL){
                stampaInventario(tabI);
            } else {
                printf("L'inventario e' vuoto!\n");
            }
            break;
        case r_calcolaStatistiche:
            if((tabPg != NULL && tabPg->headPg != NULL) && tabI != NULL){
                calcolaStatistiche(tabPg, tabI);
            } else {
                printf("Controlla di aver inserito prima sia i personaggi che l'inventario!\n");
            }
            break;
        case r_fine:
            continua = 0;
            break;
        default:
            printf("Comando errato!");
            break;
        }
    } while (continua);
    printf("Programma terminato....\n");

    // DEALLOCAZIONE
    freePersonaggi(tabPg);
    if(tabI != NULL){
        freeInventario(tabI);
    }
    return 0;
}

// FUNCTIONS
comando_e leggi_comando()
{
    comando_e c;
    char cmd[MAXL];
    char tabella[r_err][30] = {
        "carica_personaggi",
        "carica_inventario",
        "aggiungi_personaggio",
        "rimuovi_personaggio",
        "aggiungi_oggetto",
        "rimuovi_oggetto",
        "calcola_statistiche",
        "stampa_personaggi",
        "stampa_inventario",
        "fine"};

    printf("Inserisci uno tra questi comandi \n(carica_personaggi,\n carica_inventario,\n aggiungi_personaggio,\n rimuovi_personaggio,\n aggiungi_oggetto,\n rimuovi_oggetto,\n calcola_statistiche, \n stampa_personaggi,\n stampa_inventario,\n fine): ");
    scanf("%s", cmd);
    strlwr(cmd);
    printf("\n");

    c = r_caricaPersonaggi;
    while (c < r_err && strcmp(tabella[c], cmd) != 0)
    {
        c++;
    }
    return c;
}