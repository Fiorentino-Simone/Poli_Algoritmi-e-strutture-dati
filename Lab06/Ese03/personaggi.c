#include "personaggi.h"
#include <stdio.h>
#include <stdlib.h>

tabPg_t *initPersonaggi()
{
    tabPg_t *nodo = malloc(sizeof(*nodo));
    nodo->headPg = NULL;
    nodo->tailPg = NULL;
    nodo->nPg = 0;
    return nodo;
}

tabPg_t *leggiPersonaggi(tabPg_t *tabPg)
{
    Pg_t personaggio;
    FILE *fin;
    /*char filename[MAXN];

    printf("Inserisci nome del file per l'aggiunta dei personaggi: ");
    scanf("%s", filename);*/

    fin = fopen("pg.txt", "r");
    if (fin == NULL)
    {
        printf("Errore nella lettura del file!");
        exit(1);
    }

    while (!feof(fin))
    {
        personaggio.equip.inUso = 0;
        fscanf(fin, "%s%s%s%d%d%d%d%d%d",
                personaggio.codice,
                personaggio.nome,
                personaggio.classe,
                &(personaggio.stat.hp),
                &(personaggio.stat.mp),
                &(personaggio.stat.atk),
                &(personaggio.stat.def),
                &(personaggio.stat.mag),
                &(personaggio.stat.spr));
        personaggio.stat_base = personaggio.stat;
        
        inserimento_in_coda_personaggio(tabPg, personaggio);
    }

    fclose(fin);
    return tabPg;
}

void inserimento_in_coda_personaggio(tabPg_t *tabPg, Pg_t personaggio)
{
    nodoPg *new_node;

    new_node = malloc(sizeof(*new_node));
    if (new_node == NULL)
    {
        printf("Errore nell'allocazione!");
        return;
    }

    new_node->val = personaggio;
    new_node->next = NULL;
    if (tabPg->headPg == NULL)
    {
        tabPg->headPg = tabPg->tailPg = new_node;
    }
    else
    {
        tabPg->tailPg->next = new_node;
        tabPg->tailPg = new_node;
    }
    tabPg->nPg++;
}

tabPg_t *aggiungiPersonaggio(tabPg_t *tabPg)
{
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
    personaggio.stat_base = personaggio.stat;
    inserimento_in_coda_personaggio(tabPg, personaggio);

    return tabPg;
}

void rimuoviPersonaggio(tabPg_t *tabPg)
{
    char cod[MAXN];
    nodoPg *temp;

    printf("Inserisci il codice del personaggio da eliminare: ");
    scanf("%s", cod);

    temp = ricerca_codice(tabPg->headPg, cod);
    if (temp != NULL)
    {
        tabPg->headPg = elimina_codice(tabPg->headPg, &(tabPg->tailPg), temp);
        tabPg->nPg--;
    }
    else
    {
        printf("Il codice %s non e' presente nella lista!", cod);
    }
}

nodoPg *ricerca_codice(nodoPg *lista, char *cod)
{
    while (lista != NULL)
    {
        if (strcmp(lista->val.codice, cod) == 0)
        {
            return lista;
        }
        lista = lista->next;
    }
    return NULL;
}

nodoPg *elimina_codice(nodoPg *lista, nodoPg **coda, nodoPg *temp)
{
    nodoPg *x, *p;
    int ok = 0;

    if (temp == lista)
    {
        lista = lista->next;
        if (temp == *coda)
        {
            *coda = NULL;
        }
        free(temp);
    }
    else
    {
        x = lista;
        p = NULL;
        while (x != NULL && ok != 1)
        {
            if (x == temp)
            {
                if (x == *coda)
                { // nel caso mi trovassi in coda aggiorno il puntatore prima di eliminare
                    *coda = p;
                    if (p != NULL)
                    {
                        p->next = NULL;
                    }
                }
                else
                {
                    p->next = x->next;
                }
                free(temp);
                ok = 1;
            }
            else
            {
                p = x;
                x = x->next;
            }
        }
    }

    return lista;
}

void aggiungiOggetto(tabPg_t *tabPg, tabInv_t *tabI)
{
    char cod[MAXN], nome[MAXN];
    nodoPg *temp;
    int index_obj;

    printf("Inserisci il codice del personaggio a cui aggiungere l'oggetto: ");
    scanf("%s", cod);

    printf("Inserisci adesso il nome dell'oggetto che vuoi aggiungere: ");
    scanf("%s", nome);

    temp = ricerca_codice(tabPg->headPg, cod);
    index_obj = ricerca_oggetto(tabI, nome);
    if (temp != NULL && index_obj != -1)
    {
        if (temp->val.equip.inUso < MAXNEQUIP)
        {
            temp->val.equip.vettEq[temp->val.equip.inUso] = tabI->vettInv[index_obj];
            temp->val.equip.inUso++;
        }
        else
        {
            printf("Il personaggio ha gia' il numero massimo di oggetti equipaggiati!");
        }
    }
    else
    {
        printf("Il codice %s non e' presente nella lista!", cod);
    }
}

void rimuoviOggetto(tabPg_t *tabPg, tabInv_t *tabI)
{
    char cod[MAXN], nome[MAXN];
    nodoPg *temp;
    int index_obj;

    printf("Inserisci il codice del personaggio a cui aggiungere l'oggetto: ");
    scanf("%s", cod);

    printf("Inserisci adesso il nome dell'oggetto che vuoi aggiungere: ");
    scanf("%s", nome);

    temp = ricerca_codice(tabPg->headPg, cod);
    index_obj = ricerca_oggetto(tabI, nome);
    if (temp != NULL && index_obj != -1)
    {
        temp->val.equip.inUso--;
        for (int i = index_obj; i < temp->val.equip.inUso; ++i)
        {
            temp->val.equip.vettEq[i] = temp->val.equip.vettEq[i + 1];
        }
    }
    else
    {
        printf("Il codice %s non e' presente nella lista!", cod);
    }
}

void calcolaStatistiche(tabPg_t *tabPg, tabInv_t *tabI)
{
    char cod[MAXN];
    nodoPg *temp;
    int equipaggiamento[MAXNEQUIP];

    printf("Inserisci il codice del personaggio a cui calcolare le statistiche: ");
    scanf("%s", cod);

    temp = ricerca_codice(tabPg->headPg, cod);
    if (temp != NULL)
    {
        if (temp->val.equip.inUso != 0)
        {
            temp->val.stat.hp = temp->val.stat_base.hp;
            temp->val.stat.mp = temp->val.stat_base.mp;
            temp->val.stat.atk = temp->val.stat_base.atk;
            temp->val.stat.def = temp->val.stat_base.def;
            temp->val.stat.mag = temp->val.stat_base.mag;
            temp->val.stat.spr = temp->val.stat_base.spr;

            for (int i = 0; i < temp->val.equip.inUso; i++)
            {
                temp->val.stat.hp += temp->val.equip.vettEq[i].stat.hp;
                temp->val.stat.mp += temp->val.equip.vettEq[i].stat.mp;
                temp->val.stat.atk += temp->val.equip.vettEq[i].stat.atk;
                temp->val.stat.def += temp->val.equip.vettEq[i].stat.def;
                temp->val.stat.mag += temp->val.equip.vettEq[i].stat.mag;
                temp->val.stat.spr += temp->val.equip.vettEq[i].stat.spr;
            }
        }

        if (temp->val.stat.hp < 0)
            temp->val.stat.hp = 0;
        if (temp->val.stat.mp < 0)
            temp->val.stat.mp = 0;
        if (temp->val.stat.atk < 0)
            temp->val.stat.atk = 0;
        if (temp->val.stat.def < 0)
            temp->val.stat.def = 0;
        if (temp->val.stat.mag < 0)
            temp->val.stat.mag = 0;
        if (temp->val.stat.spr < 0)
            temp->val.stat.spr = 0;

        printf("Statistiche per:\n %s %s %s %d %d %d %d %d %d\n",
                temp->val.codice,
                temp->val.nome,
                temp->val.classe,
                (temp->val.stat.hp),
                (temp->val.stat.mp),
                (temp->val.stat.atk),
                (temp->val.stat.def),
                (temp->val.stat.mag),
                (temp->val.stat.spr));
    }
    else
    {
        printf("Il codice %s non e' presente nella lista!", cod);
    }
}

void stampaPersonaggi(tabPg_t *tabPg)
{
    int i;
    nodoPg *nodo;

    nodo = tabPg->headPg;
    printf("\n");
    while (nodo != NULL)
    {
        stampaPersonaggio(nodo->val);
        if (nodo->val.equip.inUso != 0)
        {
            printf("Equipaggiamento personaggio: \n");
            for (i = 0; i < nodo->val.equip.inUso; i++)
            {
                stampaEquipaggiamento(nodo, i);
            }
        }
        nodo = nodo->next;
        printf("\n");
    }
    printf("Numero Personaggi: %d\n", tabPg->nPg);
}

void stampaPersonaggio(Pg_t personaggio)
{
    printf("%s %s %s %d %d %d %d %d %d\n",
            personaggio.codice,
            personaggio.nome,
            personaggio.classe,
            personaggio.stat_base.hp,
            personaggio.stat_base.mp,
            personaggio.stat_base.atk,
            personaggio.stat_base.def,
            personaggio.stat_base.mag,
            personaggio.stat_base.spr);
}

void stampaEquipaggiamento(nodoPg *nodo, int index)
{
    printf("%s %s %d %d %d %d %d %d\n",
            nodo->val.equip.vettEq[index].nome,
            nodo->val.equip.vettEq[index].tipo,
            nodo->val.equip.vettEq[index].stat.hp,
            nodo->val.equip.vettEq[index].stat.mp,
            nodo->val.equip.vettEq[index].stat.atk,
            nodo->val.equip.vettEq[index].stat.def,
            nodo->val.equip.vettEq[index].stat.mag,
            nodo->val.equip.vettEq[index].stat.spr);
}