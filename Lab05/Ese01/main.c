#include <stdio.h>
#include <stdlib.h>

// TYPEDEF
typedef struct{
    int s, f;
} Att;

// PROTOTIPI
void read_data(int *n, Att **v);

void attSel(int n, Att *v);
void powerset(int pos, Att *v, int n, int *sol, int *bestSol, int *bestDur, int currDur);
int check(Att *v, int *sol, int n);

int main() {
    /* DICHIARAZIONE */
    int n;
    Att *v;

    read_data(&n, &v);

    attSel(n, v);

    free(v);
    return 0;
}

// FUNCTIONS
void read_data(int *n, Att **v){
    FILE *fin;

    fin = fopen("att.txt", "r");
    if(fin == NULL){
        printf("Impossibile aprire il file!");
        exit(-1);
    }

    fscanf(fin, "%d", n);
    *v = (Att *) malloc((*n) * sizeof(Att));

    for (int i = 0; i < (*n); i++) {
        fscanf(fin, "%d %d", &((*v)[i].s), &((*v)[i].f));
    }

    fclose(fin);
}

void attSel(int n, Att *v) {
    int *sol = (int *)calloc(n, sizeof(int)); // Soluzione corrente
    int *bestSol = (int *)calloc(n, sizeof(int)); // Migliore soluzione
    int bestDur = 0; // Massima durata trovata

    powerset(0, v, n, sol, bestSol, &bestDur, 0);

    printf("Migliore durata: %d\n", bestDur);
    printf("Attivita' selezionate:\n");
    for (int i = 0; i < n; i++) {
        if (bestSol[i] == 1) {
            printf("Attivita' %d: inizio=%d, fine=%d\n", i, v[i].s, v[i].f);
        }
    }

    free(sol);
    free(bestSol);
}

// Funzione per generare il powerset
void powerset(int pos, Att *v, int n, int *sol, int *bestSol, int *bestDur, int currDur) {
    if (pos >= n) {
        // Verifica se la soluzione è compatibile
        if (check(v, sol, n)) {
            // Calcola la durata totale della soluzione corrente
            if (currDur > *bestDur) {
                *bestDur = currDur;
                for (int i = 0; i < n; i++) {
                    bestSol[i] = sol[i];
                }
            }
        }
        return;
    }

    // Escludi l'attività corrente
    sol[pos] = 0;
    powerset(pos + 1, v, n, sol, bestSol, bestDur, currDur);

    // Includi l'attività corrente
    sol[pos] = 1;
    powerset(pos + 1, v, n, sol, bestSol, bestDur, currDur + (v[pos].f - v[pos].s));
}

// Funzione per verificare la compatibilità delle attività selezionate
int check(Att *v, int *sol, int n) {
    for (int i = 0; i < n; i++) {
        if (sol[i]) {
            for (int j = i + 1; j < n; j++) {
                if (sol[j]) {
                    // Verifica sovrapposizione
                    if (!(v[i].f <= v[j].s || v[j].f <= v[i].s)) {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}
