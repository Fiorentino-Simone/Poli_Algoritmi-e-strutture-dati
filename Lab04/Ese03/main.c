/*#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

// TYPEDEF
typedef struct {
    int z, r, t, s; // z --> zaffiro, r --> rubino, t --> topazio, s --> smeraldo
} Pietra;

// PROTOTIPI
void read_file(char *filename, int *n, Pietra **pietre);

int main() {
    int n;
    Pietra *pietre = NULL;

    read_file("test_file", &n, &pietre);

    for (int i = 0; i < n; i++) {
        int tot, max_lung;

        tot = pietre[i].z + pietre[i].r + pietre[i].t + pietre[i].s;
        max_lung = INT_MIN;

        printf("TEST #%d", (i+1));
        printf("\n");
        printf("zaffiro = %d, rubino = %d, topazio = %d, smeraldo = %d, TOT = %d", pietre[i].z, pietre[i].r, pietre[i].t, pietre[i].s, tot);

       4 powerset();
    }

    free(pietre);
    return 0;
}

// FUNCTIONS
void read_file(char *filename, int *n, Pietra **pietre){
    FILE *fin;

    fin = fopen(filename, "r");
    if(fin == NULL){
        printf("Errore nella lettura del file!");
        exit(-1);
    }

    fscanf(fin, "%d", n);
    *pietre = (Pietra *) malloc((*n) * sizeof(pietre));

    for (int i = 0; i < (*n); i++) {
        fscanf(fin, "%d %d %d %d", &((*pietre)[i].z), &((*pietre)[i].r), &((*pietre)[i].t), &((*pietre)[i].s));
    }

    fclose(fin);
}*/

#include <stdio.h>
#include <stdlib.h>

// Definizione della struct Pietra
typedef struct {
    int z, r, t, s; // z --> zaffiro, r --> rubino, t --> topazio, s --> smeraldo
} Pietra;

// Enum per indicare i tipi di pietre
typedef enum { ZAFFIRO, RUBINO, TOPAZIO, SMERALDO } Item;

// Funzioni
int disp_rip_pruning(int pos, int *mark, int *sol, int n, int k, int prec, int *max_len, int len_corrente);
int check(int prec, int att);
void esegui_test(Pietra pietre);

int main() {
    FILE *file = fopen("input.txt", "r");
    if (!file) {
        printf("Errore nell'apertura del file!\n");
        return 1;
    }

    int num_test;
    fscanf(file, "%d", &num_test); // Leggi il numero di test

    Pietra *tests = (Pietra *)malloc(num_test * sizeof(Pietra));
    if (!tests) {
        printf("Errore nell'allocazione della memoria!\n");
        fclose(file);
        return 1;
    }

    // Leggi i dati di ciascun test
    for (int i = 0; i < num_test; i++) {
        fscanf(file, "%d %d %d %d", &tests[i].z, &tests[i].r, &tests[i].t, &tests[i].s);
    }

    fclose(file);

    // Esegui ciascun test
    for (int i = 0; i < num_test; i++) {
        printf("Test #%d:\n", i + 1);
        esegui_test(tests[i]);
        printf("\n");
    }

    free(tests);
    return 0;
}

// Funzione per eseguire un test dato un set di pietre
void esegui_test(Pietra pietre) {
    int val[4] = {pietre.z, pietre.r, pietre.t, pietre.s};
    int mark[4] = {pietre.z, pietre.r, pietre.t, pietre.s};
    int k = val[ZAFFIRO] + val[RUBINO] + val[TOPAZIO] + val[SMERALDO]; // Lunghezza massima teorica
    int *sol = (int *)malloc(k * sizeof(int)); // Soluzione corrente
    int n = 4; // Tipi di pietre
    int max_len = 0; // Lunghezza massima trovata

    // Trova la collana massima con pruning
    disp_rip_pruning(0, mark, sol, n, k, -1, &max_len, 0);

    // Stampa il risultato
    printf("Pietre disponibili: Z=%d, R=%d, T=%d, S=%d, TOT=%d\n",
           val[ZAFFIRO], val[RUBINO], val[TOPAZIO], val[SMERALDO], k);
    printf("Collana massima di lunghezza %d\n", max_len);

    free(sol);
}

// Funzione per esplorare ricorsivamente le disposizioni ripetute con pruning
int disp_rip_pruning(int pos, int *mark, int *sol, int n, int k, int prec, int *max_len, int len_corrente) {
    int i;

    // Aggiorna la lunghezza massima
    if (len_corrente > *max_len) {
        *max_len = len_corrente;
    }

    // Caso base: impossibile proseguire
    if (len_corrente >= k) return 1;

    // Pruning: verifica se è possibile migliorare la soluzione attuale
    int max_pietre_rimanenti = 0;
    for (i = 0; i < n; i++) {
        max_pietre_rimanenti += mark[i];
    }

    // Se la lunghezza corrente più le pietre rimanenti non superano la lunghezza massima trovata, tronca
    if (len_corrente + max_pietre_rimanenti <= *max_len) return 0;

    // Prova ogni tipo di pietra
    for (i = 0; i < n; i++) {
        if (mark[i] > 0 && check(prec, i)) {
            // Scelta
            mark[i]--;     // Decrementa la pietra usata
            sol[pos] = i;  // Registra la scelta

            // Backtracking
            disp_rip_pruning(pos + 1, mark, sol, n, k, i, max_len, len_corrente + 1);

            // Undo della scelta
            mark[i]++;
        }
    }

    return 0;
}

// Funzione di controllo per validare la scelta
int check(int prec, int att) {
    if (prec == -1) return 1; // Primo elemento è sempre valido

    // Regole di validità
    if ((prec == ZAFFIRO && (att == ZAFFIRO || att == RUBINO)) ||
        (prec == SMERALDO && (att == SMERALDO || att == TOPAZIO)) ||
        (prec == RUBINO && (att == SMERALDO || att == TOPAZIO)) ||
        (prec == TOPAZIO && (att == ZAFFIRO || att == RUBINO))) {
        return 1;
    }

    return 0;
}
