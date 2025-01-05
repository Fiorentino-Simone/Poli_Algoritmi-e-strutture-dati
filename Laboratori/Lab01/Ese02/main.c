#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXL 30
#define MAXN 1000

typedef enum {
    r_date, r_partenza, r_capolinea, r_ritardo, r_ritardo_tot, r_fine, r_err
} comando_e;

typedef struct corsa {
    char codice_tratta[MAXL];
    char partenza[MAXL];
    char destinazione[MAXL];
    char data[MAXL];
    char ora_partenza[MAXL];
    char ora_arrivo[MAXL];
    int ritardo;
} corsa_t;

/* PROTOTIPI */
int leggiDati(char *filename, corsa_t *corse);
comando_e leggiComando ();
void elencoCorseDate(corsa_t *corse, int dim);
void elencoCorsePartenza(corsa_t *corse, int dim);
void elencoCorseCapolinea(corsa_t *corse, int dim);
void elencoCorseRitardo(corsa_t *corse, int dim);
void elencoCorseRitardoTratta(corsa_t *corse, int dim);
void stampa_record(corsa_t corsa);

int main() {
    /* DICHIARAZIONE */
    int continua = 1;
    comando_e comando;
    corsa_t corse[MAXN];

    int dim = leggiDati("corse.txt", corse);

    while(continua){
        comando = leggiComando();
        switch (comando) {
            case r_date: elencoCorseDate(corse, dim); break;
            case r_partenza: elencoCorsePartenza(corse, dim); break;
            case r_capolinea: elencoCorseCapolinea(corse, dim); break;
            case r_ritardo: elencoCorseRitardo(corse, dim); break;
            case r_ritardo_tot: elencoCorseRitardoTratta(corse, dim); break;
            case r_fine: continua = 0; break;
            default: printf("Comando errato!"); break;
        }
        printf("\n");
    }
    return 0;
}

/* FUNCTIONS */
int leggiDati(char *filename, corsa_t *corse){
    int dim;
    FILE *fin;

    fin = fopen("corse.txt", "r");
    if(fin == NULL){
        printf("Errore nella lettura del file!");
        exit(0);
    }
    fscanf(fin, "%d", &dim);
    for (int i=0; i<dim; i++){
        fscanf(fin, "%s%s%s%s%s%s%d",
               corse[i].codice_tratta,
               corse[i].partenza,
               corse[i].destinazione,
               corse[i].data,
               corse[i].ora_arrivo,
               corse[i].ora_partenza,
               &corse[i].ritardo);
    }
    return dim;
}

comando_e leggiComando(){
    comando_e c;
    char cmd[MAXL];
    char tabella[r_err][12] = {
            "date",
            "partenza",
            "capolinea",
            "ritardo",
            "ritardo_tot",
            "fine"
    };

    printf("Inserisci uno tra questi comandi (date, partenza, capolinea, ritardo, ritardo_tot, fine): ");
    scanf("%s", cmd);
    strlwr(cmd);
    printf("\n");

    c = r_date;
    while (c < r_err && strcmp(tabella[c], cmd) != 0){
        c++;
    }
    return c;
}

void elencoCorseDate(corsa_t *corse, int dim){
    char data_inizio[MAXL], data_fine[MAXL];
    printf("Inserisci due date nel formato (yyyy/mm/dd): ");
    scanf("%s %s",data_inizio,data_fine);
    printf("\n");

    for (int i=0; i<dim; i++){
        if((strcmp(data_inizio, corse[i].data) <= 0) && (strcmp(data_fine, corse[i].data) >= 0)){
            stampa_record(corse[i]);
        }
    }
}

void elencoCorsePartenza(corsa_t *corse, int dim){
    char fermata[MAXL];

    printf("Inserisci una fermata: ");
    scanf("%s", fermata);

    printf("\n");
    printf("Le tratte che partono con %s sono: ", fermata);
    printf("\n");
    for (int i=0; i<dim; i++){
        if(strcmp(corse[i].partenza, fermata) == 0){
            stampa_record(corse[i]);
        }
    }
}

void elencoCorseCapolinea(corsa_t *corse, int dim){
    char capolinea[MAXL];

    printf("Inserisci la capolinea: ");
    scanf("%s", capolinea);
    printf("\n");

    printf("Le tratte che terminano con %s sono: ", capolinea);
    printf("\n");
    for (int i = 0; i<dim; i++){
        if(strcmp(corse[i].destinazione, capolinea) == 0){
            stampa_record(corse[i]);
        }
    }
}

void elencoCorseRitardo(corsa_t *corse, int dim){
    char data_inizio[MAXL], data_fine[MAXL];

    printf("Inserisci due date nel formato (yyyy/mm/dd): ");
    scanf("%s %s",data_inizio,data_fine);
    printf("\n");

    printf("Le tratte che sono arrivate in ritardo nel range di date sono: ");
    printf("\n");
    for (int i=0; i<dim; i++){
        if(corse[i].ritardo > 0){
            if((strcmp(data_inizio, corse[i].data) <= 0) && (strcmp(data_fine, corse[i].data) >= 0)){
                stampa_record(corse[i]);
            }
        }
    }
}

void elencoCorseRitardoTratta(corsa_t *corse, int dim){
    char codice_tratta[MAXL];
    int ritardo_complessivo = 0;

    printf("Inserisci un codice tratta: ");
    scanf("%s", codice_tratta);
    printf("\n");

    for (int i=0; i<dim; i++){
        if(strcmp(corse[i].codice_tratta, codice_tratta) == 0){
            ritardo_complessivo += corse[i].ritardo;
        }
    }

    printf("Il ritardo complessimo accumulato dalla tratta con codice %s risulta: %d", codice_tratta, ritardo_complessivo);
    printf("\n");
}

void stampa_record(corsa_t corsa){
    printf("%s %s %s %s %s %s %d",
           corsa.codice_tratta,
           corsa.partenza,
           corsa.destinazione,
           corsa.data,
           corsa.ora_arrivo,
           corsa.ora_partenza,
           corsa.ritardo);
    printf("\n");
}