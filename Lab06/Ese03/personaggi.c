#include "personaggi.h"
#include <stdio.h>
#include <stdlib.h>

tabPg_t *initPersonaggi(){
    tabPg_t *nodo = malloc(sizeof(* nodo));
    nodo->headPg = NULL;
    nodo->tailPg = NULL;
    nodo->nPg = 0;
    return nodo;
}

tabPg_t* leggiPersonaggi(tabPg_t *tabPg){
    Pg_t personaggio;
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
        personaggio.equip.inUso=0;
        fscanf(fin,"%s%s%s%d%d%d%d%d%d",
               personaggio.codice,
               personaggio.nome,
               personaggio.classe,
               &(personaggio.stat.hp),
               &(personaggio.stat.mp),
               &(personaggio.stat.atk),
               &(personaggio.stat.def),
               &(personaggio.stat.mag),
               &(personaggio.stat.spr));

        inserimento_in_coda_personaggio(tabPg, personaggio);
    }

    fclose(fin);
    return tabPg;
}

void inserimento_in_coda_personaggio(tabPg_t *tabPg, Pg_t personaggio){
    nodoPg *new_node;

    new_node = malloc(sizeof(*new_node));
    if(new_node == NULL){
        printf("Errore nell'allocazione!");
        return;
    }

    new_node->val = personaggio;
    new_node->next = NULL;
    if(tabPg->headPg==NULL){
        tabPg->headPg = tabPg->tailPg = new_node;
    }else{
        tabPg->tailPg->next = new_node; //TODO: controllo di questa linea
        tabPg->tailPg = new_node;
    }
    tabPg->nPg++;
}

tabPg_t* aggiungiPersonaggio(tabPg_t *tabPg){
    Pg_t personaggio;

    printf("Per inserire il nuovo personaggio devi scrivere le sue informazioni, separate da spazio: ");
    printf("\n Le informazioni sono relative a 'codice nome classe hp mp atk def mag spr': ");
    scanf("%s %s %s %d %d %d %d %d %d",
          personaggio.codice,
          personaggio.nome,
          personaggio.classe,
          &(personaggio.stat.hp),
          &(personaggio.stat.mp),
          &(personaggio.stat.atk),
          &(personaggio.stat.def),
          &(personaggio.stat.mag),
          &(personaggio.stat.spr));
    personaggio.equip.inUso = 0;
    inserimento_in_coda_personaggio(tabPg, personaggio);

    return tabPg;
}

void rimuoviPersonaggio(tabPg_t *tabPg){
    char cod[MAXN];
    nodoPg *temp;

    printf("Inserisci il codice del personaggio da eliminare: ");
    scanf("%s", cod);

    temp = ricerca_codice(tabPg->headPg, cod);
    if(temp != NULL) {
        tabPg->headPg = elimina_codice(tabPg->headPg, temp);
        tabPg->nPg--;
    } else {
        printf("Il codice %s non e' presente nella lista!", cod);
    }
}

nodoPg *ricerca_codice(nodoPg *lista, char *cod){
    while(lista != NULL){
        if(strcmp(lista->val.codice, cod) == 0){
            return lista;
        }
        lista = lista->next;
    }
    return NULL;
}

nodoPg *elimina_codice(nodoPg *lista, nodoPg *temp){
    nodoPg *x, *p;
    int ok = 0;

    // x = lista;
    // p = NULL;

    // while(x != NULL && ok != 1){
    //     if(x == temp){
    //         if(p == NULL){
    //             lista = x->next;
    //         } else {
    //             p->next = x -> next;
    //         }
    //         free(temp);
    //         ok = 1;
    //     }
    //     p = x;
    //     x = x->next;
    // }


    // I have a problem: when i delete the last element and i want to after add a new element in the tail that one is not added
    // I think that the problem is in the tailPg, because i don't update it
    // You must show me another code to delete element but also update the tailPg

    if(temp == lista){
        lista = lista->next;
        free(temp);
    } else {
        x = lista;
        while(x != NULL && x != temp){
            p = x;
            x = x->next;
        }
        if(x != NULL){
            p->next = x->next;
            free(x);
        }
    }

    // TODO: error in the tailPg

    




    return lista;
}

void stampaPersonaggi(tabPg_t *tabPg){
    int i;
    nodoPg *nodo;

    nodo = tabPg->headPg;
    printf("\n");
    while(nodo != NULL){
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
        if(nodo->val.equip.inUso != 0){
            printf("Equipaggiamento personaggio\n");
            for(i=0; i < nodo->val.equip.inUso; i++){
                stampaEquipaggiamento(nodo, i);
            }
        }
        nodo = nodo->next;
        printf("\n");
    }
    printf("Numero Personaggi Attuali : %d\n", tabPg->nPg);
}

void stampaEquipaggiamento(nodoPg *nodo, int index){
    //TODO: fare una print più esplicita (dicendo il nome della chiavi)
    printf("%s %s %d %d %d %d %d %d\n",
           nodo->val.equip.vettEq[index].nome,
           nodo->val.equip.vettEq[index].tipo,
           nodo->val.equip.vettEq[index].stat.hp,
           nodo->val.equip.vettEq[index].stat.mp,
           nodo->val.equip.vettEq[index].stat.atk,
           nodo->val.equip.vettEq[index].stat.def,
           nodo->val.equip.vettEq[index].stat.mag,
           nodo->val.equip.vettEq[index].stat.spr
    );
}