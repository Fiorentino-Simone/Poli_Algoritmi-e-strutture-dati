#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXL 30

// TYPEDEF
typedef enum {
    r_stampa, r_ordData, r_ordCod, r_ordPartenza, r_ordDestinazione, r_ricercaPartenza, r_leggiFile, r_fine, r_err
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
int leggi_dati(char *filename, corsa_t **corse);
comando_e leggi_comando();
void stampa_log(corsa_t *corse, int dim);
void stampa_record(corsa_t **corse, int dim);

void ordRifCorsePerData(corsa_t *elRif0[], int dim);
void ordRifCorsePerTratta(corsa_t *elRif1[], int dim);
void ordRifCorsePerPartenza(corsa_t *elRif2[], int dim);
void ordRifCorsePerDest(corsa_t *elRif3[], int dim);

void ricerca_lineare(corsa_t *corse, int dim, char *stazione_ricerca, int len);
void ricerca_dicotomica(corsa_t **corse, int dim, char *stazione_ricerca);

void dealloca_rif(corsa_t  **elRif0, corsa_t  **elRif1, corsa_t  **elRif2, corsa_t  **elRif3, corsa_t *corse);
void alloca_rif(corsa_t  ***elRif0, corsa_t  ***elRif1, corsa_t  ***elRif2, corsa_t  ***elRif3, corsa_t *corse, int dim);

int main() {
    // DICHIARAZIONE
    int continua = 1;
    comando_e comando;
    corsa_t *corse;

    char stazione_ricerca[MAXL];
    char filename[MAXL];

    // VETTORI DI PUNTATORI PER ORDINAMENTI
    corsa_t **elRif0, **elRif1, **elRif2, **elRif3;

    int dim = leggi_dati("corse.txt", &corse);

    alloca_rif(&elRif0, &elRif1, &elRif2, &elRif3, corse, dim);

    while(continua){
        int scelta;
        comando = leggi_comando();
        switch (comando) {
            case r_stampa: stampa_log(corse, dim); break;
            case r_ordData: 
                ordRifCorsePerData(elRif0, dim); 
                stampa_record(elRif0, dim);
                break;
            case r_ordCod:
                ordRifCorsePerTratta(elRif1, dim);
                stampa_record(elRif1, dim);
                break;
            case r_ordPartenza:
                ordRifCorsePerPartenza(elRif2, dim);
                stampa_record(elRif2, dim);
                break;
            case r_ordDestinazione:
                ordRifCorsePerDest(elRif3, dim);
                stampa_record(elRif3, dim);
                break;
            case r_ricercaPartenza:
                printf("Inserisci la stazione di partenza da cercare: ");
                scanf("%s", stazione_ricerca);

                printf("Inserisci 1 per la ricerca lineare oppure 2 per la ricerca dicotomica: ");
                scanf("%d", &scelta);
                if(scelta == 1){
                    ricerca_lineare(corse, dim, stazione_ricerca, strlen(stazione_ricerca));
                } else if(scelta == 2) {
                    ordRifCorsePerPartenza(elRif2, dim);
                    ricerca_dicotomica(elRif2, dim, stazione_ricerca);
                }
                break;
            case r_leggiFile:
                printf("Inserisci il nome del file da leggere: ");
                scanf("%s", filename);

                dealloca_rif(elRif0, elRif1, elRif2, elRif3, corse);
                dim = leggi_dati(filename, &corse);
                alloca_rif(&elRif0, &elRif1, &elRif2, &elRif3, corse, dim);
                break;
            case r_fine: continua = 0; break;
            default: printf("Comando errato!"); break;
        }
        printf("\n");
    }

    /* DEALLOCAZIONE */
    dealloca_rif(elRif0, elRif1, elRif2, elRif3, corse);
    return 0;
}

// FUNCTIONS
int leggi_dati(char *filename, corsa_t **_corse){
    int dim;
    FILE *fin;
    corsa_t *corse;

    fin = fopen(filename, "r");
    if(fin == NULL){
        printf("Errore nella lettura del file!");
        exit(1);
    }
    fscanf(fin, "%d", &dim);
    corse = (corsa_t *) malloc(sizeof(corsa_t) * dim);
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

    *_corse = corse;

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
            "leggi_file",
            "fine"
    };

    printf("Inserisci uno tra questi comandi (stampa, ord_data, ord_tratta, ord_partenza, ord_dest, ricerca_stazione, leggi_file, fine): ");
    scanf("%s", cmd);
    strlwr(cmd);
    printf("\n");

    c = r_stampa;
    while (c < r_err && strcmp(tabella[c], cmd) != 0){
        c++;
    }
    return c;
}

void dealloca_rif(corsa_t  **elRif0, corsa_t  **elRif1, corsa_t  **elRif2, corsa_t  **elRif3, corsa_t *corse){
    free(elRif0);
    free(elRif1);
    free(elRif2);
    free(elRif3);
    free(corse);
}

void alloca_rif(corsa_t  ***_elRif0, corsa_t  ***_elRif1, corsa_t  ***_elRif2, corsa_t  ***_elRif3, corsa_t *corse, int dim){
    corsa_t **elRif0, **elRif1, **elRif2, **elRif3;

    elRif0 = (corsa_t **) malloc ( dim * sizeof(corsa_t *));
    elRif1 = (corsa_t **) malloc ( dim * sizeof(corsa_t *));
    elRif2 = (corsa_t **) malloc ( dim * sizeof(corsa_t *));
    elRif3 = (corsa_t **) malloc ( dim * sizeof(corsa_t *));

    for (int i = 0; i < dim; ++i) {
        elRif0[i] = elRif1[i] = elRif2[i] = elRif3[i] = &corse[i];
    }

    *_elRif0 = elRif0;
    *_elRif1 = elRif1;
    *_elRif2 = elRif2;
    *_elRif3 = elRif3;
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

void stampa_record(corsa_t **corse, int dim){
    for (int i=0; i<dim; i++){
        printf("Codice Tratta: %s, Partenza: %s, Destinazione: %s, Data: %s, Arrivo: %s, Partenza: %s, Ritardo: %d",
               corse[i]->codice_tratta,
               corse[i]->partenza,
               corse[i]->destinazione,
               corse[i]->data,
               corse[i]->ora_arrivo,
               corse[i]->ora_partenza,
               corse[i]->ritardo);
        printf("\n");
    }
}

void ordRifCorsePerData(corsa_t *elRif0[], int dim){
    corsa_t *temp;
    int l = 0, r = dim - 1;

    for (int i = l; i < r; i++) {
        for (int j = l; j < r - i +l; j++) {
            if(strcmp(elRif0[j]->data, elRif0[j+1]->data) > 0){
                temp = elRif0[j];
                elRif0[j] = elRif0[j+1];
                elRif0[j+1] = temp;
            }
        }
    }
}

void ordRifCorsePerTratta(corsa_t *elRif1[], int dim){
    corsa_t *temp;
    int l = 0, r = dim - 1;

    for (int i = l; i < r; i++) {
        for (int j = l; j < r - i +l; j++) {
            if(strcmp(elRif1[j]->codice_tratta, elRif1[j+1]->codice_tratta) > 0){
                temp = elRif1[j];
                elRif1[j] = elRif1[j+1];
                elRif1[j+1] = temp;
            }
        }
    }
}

void ordRifCorsePerPartenza(corsa_t *elRif2[], int dim){
    corsa_t *temp;
    int l = 0, r = dim - 1;

    for (int i = l; i < r; i++) {
        for (int j = l; j < r - i +l; j++) {
            if(strcmp(elRif2[j]->partenza, elRif2[j+1]->partenza) > 0){
                temp = elRif2[j];
                elRif2[j] = elRif2[j+1];
                elRif2[j+1] = temp;
            }
        }
    }
}

void ordRifCorsePerDest(corsa_t *elRif3[], int dim){
    corsa_t *temp;
    int l = 0, r = dim - 1;

    for (int i = l; i < r; i++) {
        for (int j = l; j < r - i +l; j++) {
            if(strcmp(elRif3[j]->destinazione, elRif3[j+1]->destinazione) > 0){
                temp = elRif3[j];
                elRif3[j] = elRif3[j+1];
                elRif3[j+1] = temp;
            }
        }
    }
}

void ricerca_lineare(corsa_t corse[], int dim, char *stazione_ricerca, int len){
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

void ricerca_dicotomica(corsa_t **corse, int dim, char *stazione_ricerca){
    int l = 0, r = dim - 1, trovato = 0;

    while (l <= r) {
        int m = (l + r) / 2;
        if (strncmp(corse[m]->partenza, stazione_ricerca, strlen(stazione_ricerca)) == 0) {
            trovato = 1;

            int i = m;
            while (i > 0 && strncmp(corse[i - 1]->partenza, stazione_ricerca, strlen(stazione_ricerca)) == 0) {
                i--;
            }
            while (i < dim && strncmp(corse[i]->partenza, stazione_ricerca, strlen(stazione_ricerca)) == 0) {
                printf("Codice Tratta: %s, Partenza: %s, Destinazione: %s, Data: %s, Arrivo: %s, Partenza: %s, Ritardo: %d",
                       corse[i]->codice_tratta,
                       corse[i]->partenza,
                       corse[i]->destinazione,
                       corse[i]->data,
                       corse[i]->ora_arrivo,
                       corse[i]->ora_partenza,
                       corse[i]->ritardo);
                printf("\n");
                i++;
            }
            break;
        } else if (strcmp(corse[m]->partenza, stazione_ricerca) < 0) {
            l = m + 1;
        } else {
            r = m - 1;
        }
    }

    if (!trovato) {
        printf("Nessuna tratta trovata per la stazione di partenza: %s\n", stazione_ricerca);
    }
}