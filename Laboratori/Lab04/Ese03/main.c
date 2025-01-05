#include <stdio.h>
#include <stdlib.h>

// TYPEDEF
typedef struct
{
    int z, r, t, s; 
} Pietra;

typedef enum
{
    ZAFFIRO,
    RUBINO,
    TOPAZIO,
    SMERALDO
} Item;

// PROTOTIPI
void read_file(char *filename, int *n, Pietra **pietre);

int powerset(int pos, int *mark, int *sol, int n, int k, int prec, int *max_len, int len_corrente);
int check(int precedente, int attuale);

void esegui_test(Pietra pietre);

int main()
{
    // DICHIARAZIONE 
    Pietra *pietre;
    int n;
    
    read_file("input.txt", &n, &pietre);

    for (int i = 0; i < n; i++)
    {
        printf("Test #%d:\n", (i + 1));
        esegui_test(pietre[i]);
        printf("\n");
    }

    free(pietre);
    return 0;
}

// FUNCTIONS
void read_file(char *filename, int *n, Pietra **pietre)
{
    FILE *fin;
    
    fin = fopen(filename, "r");
    if (fin == NULL)
    {
        printf("Errore nell'apertura del file!\n");
        exit(1);
    }

    fscanf(fin, "%d", n);

    *pietre = (Pietra *) malloc((*n) * sizeof(Pietra));
    for (int i = 0; i < (*n); i++)
    {
        fscanf(fin, "%d %d %d %d", &((*pietre)[i].z), &((*pietre)[i].r), &((*pietre)[i].t), &((*pietre)[i].s));
    }

    fclose(fin);
}

void esegui_test(Pietra pietre)
{
    int val[4] = {pietre.z, pietre.r, pietre.t, pietre.s};
    int mark[4] = {pietre.z, pietre.r, pietre.t, pietre.s};
    int k = val[ZAFFIRO] + val[RUBINO] + val[TOPAZIO] + val[SMERALDO];
    int *sol = (int *)malloc(k * sizeof(int));
    int n = 4;
    int max_len = 0;

    powerset(0, mark, sol, n, k, -1, &max_len, 0);

    printf("Pietre disponibili: Z=%d, R=%d, T=%d, S=%d, TOT=%d\n",
            val[ZAFFIRO], val[RUBINO], val[TOPAZIO], val[SMERALDO], k);
    printf("Collana massima di lunghezza: %d\n", max_len);

    free(sol);
}

int powerset(int pos, int *mark, int *sol, int n, int k, int prec, int *max_len, int len_corrente)
{
    int i;
    if (len_corrente > *max_len) {
        *max_len = len_corrente;
    }
    if (len_corrente >= k){ // Caso di terminazione
        return 1;
    }

    // Pruning: se la lunghezza corrente più le pietre rimanenti non superano la lunghezza massima trovata, ritorna
    int max_pietre_rimanenti = 0;
    for (i = 0; i < n; i++) {
        max_pietre_rimanenti += mark[i];
    }
    if ((len_corrente + max_pietre_rimanenti) <= *(max_len)){
        return 0;
    }

    for (i = 0; i < n; i++) {
        if (mark[i] > 0 && check(prec, i)) {
            mark[i]--;
            sol[pos] = i;
            powerset(pos + 1, mark, sol, n, k, i, max_len, len_corrente + 1);
            mark[i]++;
        }
    }

    return 0;
}

int check(int precedente, int attuale)
{
    if (precedente == -1)  // Caso in cui mi trovo alla prima pietra, sempre valido
    {
        return 1;
    }

    if ((precedente == ZAFFIRO && (attuale == ZAFFIRO || attuale == RUBINO)) ||
        (precedente == SMERALDO && (attuale == SMERALDO || attuale == TOPAZIO)) ||
        (precedente == RUBINO && (attuale == SMERALDO || attuale == TOPAZIO)) ||
        (precedente == TOPAZIO && (attuale == ZAFFIRO || attuale == RUBINO)))
    {
        return 1;
    }

    return 0;
}