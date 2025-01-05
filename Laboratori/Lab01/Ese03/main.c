#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXL 30
#define MAXN 1000

// TYPEDEF
typedef enum {
    r_stampa, r_ordData, r_ordCod, r_ordPartenza, r_ordDestinazione, r_ricercaPartenza, r_fine, r_err
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

// PROTOTIPI
int leggi_dati(char *filename, corsa_t *corse);
comando_e leggi_comando();
void stampa_log(corsa_t *corse, int dim);

void ordCorsePerData(corsa_t *corse, int dim);
void ordCorsePerTratta(corsa_t *corse, int dim);
void ordCorsePerPartenza(corsa_t *corse, int dim);
void ordCorsePerDest(corsa_t *corse, int dim);

void ricerca_lineare(corsa_t *corse, int dim, char *stazione_ricerca, int len);
void ricerca_dicotomica(corsa_t *corse, int dim, char *stazione_ricerca);

int main() {
    // DICHIARAZIONE
    int continua = 1;
    comando_e comando;
    corsa_t corse[MAXN];

    char stazione_ricerca[MAXL];

    int dim = leggi_dati("corse.txt", corse);

    while(continua){
        int scelta;
        comando = leggi_comando();
        switch (comando) {
            case r_stampa: stampa_log(corse, dim); break;
            case r_ordData:
                ordCorsePerData(corse, dim);
                stampa_log(corse, dim);
                break;
            case r_ordCod:
                ordCorsePerTratta(corse, dim);
                stampa_log(corse, dim);
                break;
            case r_ordPartenza:
                ordCorsePerPartenza(corse, dim);
                stampa_log(corse, dim);
                break;
            case r_ordDestinazione:
                ordCorsePerDest(corse, dim);
                stampa_log(corse, dim);
                break;
            case r_ricercaPartenza:
                printf("Inserisci la stazione di partenza da cercare: ");
                scanf("%s", stazione_ricerca);

                printf("Inserisci 1 per la ricerca lineare oppure 2 per la ricerca dicotomica: ");
                scanf("%d", &scelta);
                if(scelta == 1){
                    ricerca_lineare(corse, dim, stazione_ricerca, strlen(stazione_ricerca));
                } else if(scelta == 2) {
                    ordCorsePerPartenza(corse, dim);
                    ricerca_dicotomica(corse, dim, stazione_ricerca);
                }
                break;
            case r_fine: continua = 0; break;
            default: printf("Comando errato!"); break;
        }
        printf("\n");
    }
    return 0;
}

// FUNCTIONS
int leggi_dati(char *filename, corsa_t *corse){
    int dim;
    FILE *fin;

    fin = fopen(filename, "r");
    if(fin == NULL){
        printf("Errore nella lettura del file!");
        exit(1);
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

comando_e leggi_comando(){
    comando_e c;
    char cmd[MAXL];
    char tabella[r_err][17] = {
            "stampa",
            "ord_data",
            "ord_tratta",
            "ord_partenza",
            "ord_dest",
            "ricerca_stazione",
            "fine"
    };

    printf("Inserisci uno tra questi comandi (stampa, ord_data, ord_tratta, ord_partenza, ord_dest, ricerca_stazione, fine): ");
    scanf("%s", cmd);
    strlwr(cmd); // lower case a tutta la stringa
    printf("\n");

    c = r_stampa;
    while (c < r_err && strcmp(tabella[c], cmd) != 0){
        c++;
    }
    return c;
}

void stampa_log(corsa_t *corse, int dim){
    for (int i=0; i<dim; i++){
        printf("Codice Tratta: %s, Partenza: %s, Destinazione: %s, Data: %s, Arrivo: %s, Partenza: %s, Ritardo: %d",
               corse[i].codice_tratta,
               corse[i].partenza,
               corse[i].destinazione,
               corse[i].data,
               corse[i].ora_arrivo,
               corse[i].ora_partenza,
               corse[i].ritardo);
        printf("\n");
    }
}

void ordCorsePerData(corsa_t *corse, int dim){
    corsa_t temp;
    int l = 0, r = dim - 1;

    for (int i = l; i < r; i++) {
        for (int j = l; j < r - i +l; j++) {
            if(strcmp(corse[j].data, corse[j+1].data) > 0){
                temp = corse[j];
                corse[j] = corse[j+1];
                corse[j+1] = temp;
            }
        }
    }
}

void ordCorsePerTratta(corsa_t *corse, int dim){
    corsa_t temp;
    int l = 0, r = dim - 1;

    for (int i = l; i < r; i++) {
        for (int j = l; j < r - i +l; j++) {
            if(strcmp(corse[j].codice_tratta, corse[j+1].codice_tratta) > 0){
                temp = corse[j];
                corse[j] = corse[j+1];
                corse[j+1] = temp;
            }
        }
    }
}

void ordCorsePerPartenza(corsa_t *corse, int dim){
    corsa_t temp;
    int l = 0, r = dim - 1;

    for (int i = l; i < r; i++) {
        for (int j = l; j < r - i +l; j++) {
            if(strcmp(corse[j].partenza, corse[j+1].partenza) > 0){
                temp = corse[j];
                corse[j] = corse[j+1];
                corse[j+1] = temp;
            }
        }
    }
}

void ordCorsePerDest(corsa_t *corse, int dim){
    corsa_t temp;
    int l = 0, r = dim - 1;

    for (int i = l; i < r; i++) {
        for (int j = l; j < r - i +l; j++) {
            if(strcmp(corse[j].destinazione, corse[j+1].destinazione) > 0){
                temp = corse[j];
                corse[j] = corse[j+1];
                corse[j+1] = temp;
            }
        }
    }
}

void ricerca_lineare(corsa_t *corse, int dim, char *stazione_ricerca, int len){
    int trovato = -1;
    for (int i = 0; i < dim; ++i) {
        if(strncmp(corse[i].partenza, stazione_ricerca, len) == 0){
            printf("Codice Tratta: %s, Partenza: %s, Destinazione: %s, Data: %s, Arrivo: %s, Partenza: %s, Ritardo: %d",
                   corse[i].codice_tratta,
                   corse[i].partenza,
                   corse[i].destinazione,
                   corse[i].data,
                   corse[i].ora_arrivo,
                   corse[i].ora_partenza,
                   corse[i].ritardo);
            printf("\n");
            trovato = 0;
        }
    }

    if(trovato == -1){
        printf("Nessuna tratta trovata per la stazione di partenza: %s\n", stazione_ricerca);
    }
}

void ricerca_dicotomica(corsa_t *corse, int dim, char *stazione_ricerca){
    int l = 0, r = dim - 1, trovato = 0;

    while (l <= r) {
        int m = (l + r) / 2;
        if (strncmp(corse[m].partenza, stazione_ricerca, strlen(stazione_ricerca)) == 0) {
            trovato = 1;

            int i = m;
            while (i > 0 && strncmp(corse[i - 1].partenza, stazione_ricerca, strlen(stazione_ricerca)) == 0) {
                i--;
            }
            while (i < dim && strncmp(corse[i].partenza, stazione_ricerca, strlen(stazione_ricerca)) == 0) {
                printf("Codice Tratta: %s, Partenza: %s, Destinazione: %s, Data: %s, Arrivo: %s, Partenza: %s, Ritardo: %d",
                       corse[i].codice_tratta,
                       corse[i].partenza,
                       corse[i].destinazione,
                       corse[i].data,
                       corse[i].ora_arrivo,
                       corse[i].ora_partenza,
                       corse[i].ritardo);
                printf("\n");
                i++;
            }
            break;
        } else if (strcmp(corse[m].partenza, stazione_ricerca) < 0) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    if (!trovato) {
        printf("Nessuna tratta trovata per la stazione di partenza: %s\n", stazione_ricerca);
    }
}