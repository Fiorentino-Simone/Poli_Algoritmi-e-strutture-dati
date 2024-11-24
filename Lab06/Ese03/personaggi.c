#include "personaggi.h"
#include <stdio.h>
#include <stdlib.h>

tabPg_t *inizializzazionePersonaggi(){
    tabPg_t *nodo = malloc(sizeof(* nodo));
    nodo->headPg = NULL;
    nodo->tailPg = NULL;
    nodo->nPg = 0;
    return nodo;
}

tabPg_t* leggiPersonaggi(tabPg_t *tabPg){
    Pg_t personaggi;
    FILE *fin;
    /*char filename[MAXN];

    printf("Inserisci nome del file per l'aggiunta dei personaggi: ");
    scanf("%s", filename);*/

    fin = fopen("pg.txt", "r");
    if(fin == NULL){
        printf("Errore nella lettura del file!");
        exit(1);
    }

    while(!feof(fin)) {
        personaggi.equip.inUso=0;
        fscanf(fin,"%s%s%s%d%d%d%d%d%d",
               personaggi.codice,
               personaggi.nome,
               personaggi.classe,
               &(personaggi.stat.hp),
               &(personaggi.stat.mp),
               &(personaggi.stat.atk),
               &(personaggi.stat.def),
               &(personaggi.stat.mag),
               &(personaggi.stat.spr));

        inserimento_in_testa_personaggio(tabPg, personaggi);
    }

    fclose(fin);
    return tabPg;
}

void inserimento_in_testa_personaggio(tabPg_t *tabPg, Pg_t personaggi){
    nodoPg *new_node;

    new_node = malloc(sizeof(*new_node));
    if(new_node == NULL){
        printf("Errore nell'allocazione!");
        return;
    }

    new_node->val = personaggi;
    new_node->next = NULL;
    if(tabPg->headPg==NULL){
        tabPg->headPg = tabPg->tailPg = new_node;
    }else{
        tabPg->tailPg->next = new_node;
        tabPg->tailPg = new_node;
    }
    tabPg->nPg++;
}

void stampaPersonaggi(tabPg_t *tabp){
    nodoPg *nodo;
    nodo=tabp->headPg;
    printf("\n");
    int i;
    printf("PROVCA");
    while(nodo!=NULL){
        printf("%s %s %s %d %d %d %d %d %d\n",
               nodo->val.codice,
               nodo->val.nome,
               nodo->val.classe,
               (nodo->val.stat.hp),
               (nodo->val.stat.mp),
               (nodo->val.stat.atk),
               (nodo->val.stat.def),
               (nodo->val.stat.mag),
               (nodo->val.stat.spr));
        if(nodo->val.equip.inUso!=0){
            printf("Equipaggiamento personaggio\n");
            for(i=0;i<nodo->val.equip.inUso;i++){
                stampaequippagiamentopersonaggio(nodo,i);
            }
        }
        nodo=nodo->next;
        printf("\n");
    }
    printf("Numero Personaggi Attuali : %d\n",tabp->nPg);
}

void stampaequippagiamentopersonaggio(nodoPg *nodo,int i){
    printf("%s %s %d %d %d %d %d %d\n",
           nodo->val.equip.vettEq[i].nome,
           nodo->val.equip.vettEq[i].tipo,
           nodo->val.equip.vettEq[i].stat.hp,
           nodo->val.equip.vettEq[i].stat.mp,
           nodo->val.equip.vettEq[i].stat.atk,
           nodo->val.equip.vettEq[i].stat.def,
           nodo->val.equip.vettEq[i].stat.mag,
           nodo->val.equip.vettEq[i].stat.spr
    );
}