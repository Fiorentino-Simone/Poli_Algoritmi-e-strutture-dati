#include <stdio.h>
#include <stdlib.h>

void printMatr(int **dist, int N);
void obiettivo_one(int **dist, int N, int dist_max);
void obiettivo_two(int **dist, int N, int max_stazioni, int *pop);

int main() {

    /*
     * FORMATO PROPOSTO:
     * N --> numero di comuni
     * N righe con gli N valori uno per colonna
     * Vettore pop
    */

    FILE *fin;
    int N;
    int **dist;
    int *pop;
    int dist_max = 0;
    int max_stazioni = 0;

    fin = fopen("comuni.txt", "r");
    if(fin == NULL){
        printf("Errore nell'apertura del file!");
        exit(-1);
    }

    fscanf(fin, "%d\n", &N);
    dist = (int **) calloc(N, sizeof (int *));
    for (int i = 0; i < N; i++) {
        dist[i] = (int *) calloc(N, sizeof (int));
        for (int j = 0; j < N; j++) {
            fscanf(fin, "%d", &dist[i][j]);
        }
    }

    printMatr(dist, N);
    pop = (int *) calloc(N, sizeof (int));
    for (int i = 0; i < N; i++) {
        fscanf(fin, "%d", &pop[i]);
    }


    // funzione obiettivo 1
    printf("\nInserisci il valore di dist_max: ");
    scanf("%d", &dist_max);
    obiettivo_one(dist, N, dist_max);

    // funzione obiettivo 2
    printf("Inserisci le stazioni max da posizionare: ");
    scanf("%d", &max_stazioni);
    obiettivo_two(dist, N, max_stazioni, pop);

    fclose(fin);
    free(dist);
    free(pop);
    return 0;
}

// FUNCTIONS
void printMatr(int **dist, int N){
    for (int i = 0; i < N; i++) {
        printf("\n");
        for (int j = 0; j < N; j++) {
            printf(" %d ", dist[i][j]);
        }
    }
}

static int isValid(int *sol, int k, int **dist, int N, int dist_max){
    // Check se valida e stampa la soluzione
    int *x, *min;
    x = (int *) calloc(N, sizeof(int)); // vettore che si salva gli indici delle colonne
    min = (int *) calloc(N, sizeof(int));

    for (int i = 0; i < N; i++) {
        min[i] = 10000;
    }

    for (int i = 0; i < N; i++) {
        for (int j = 0; j < k; j++) {
            if(dist[sol[j]][i] < min[i]){
                min[i] = dist[sol[j]][i];
                x[i] = sol[j];
            }
        }
    }

    for (int i = 0; i < N; i++) {
        if(min[i] > dist_max){
            free(min);
            free(x);
            return 0;
        }
    }

    printf("La soluzione sol = (");
    for (int i = 0; i < k; i++) {
        printf(" %d ", sol[i]);
    }
    printf(")\n");
    printf("\nstampa delle scelte: ");
    printf("\n");
    for (int j = 0; j < N; j++) {
        printf("dist[%d][%d] = %d \n", x[j], j, dist[x[j]][j]);
    }

    free(min);
    free(x);
    return 1;

}

static void comb_sempl(int pos, int start, int k, int *sol, int N, int *stop, int **dist, int dist_max){
    if ((*stop) == 1) return;

    if(pos >= k){
        if(isValid(sol, k, dist, N, dist_max)){
            (*stop) = 1;
        }
        return;
    }

    for (int i = start; i < N; i++) {
        sol[pos] = i; // l'indice che identifica il comune
        comb_sempl(pos+1, i+1, k, sol, N, stop, dist, dist_max);
    }
}

void obiettivo_one(int **dist, int N, int dist_max){
    int pos = 0;
    int start = 0;
    int stop = 0;
    int k = 1;

    int *sol = (int *) calloc(N, sizeof(int));
    for (k = 1; k <= N && stop == 0; k++) {
        comb_sempl(pos, start, k, sol, N, &stop, dist, dist_max);
    }

    free(sol);
}

static int calcolaDistMin(int *sol, int **dist, int max_stazioni, int i, int *cnt){
    int min = 10000;
    for (int j = 0; j < max_stazioni; j++) {
        if(dist[sol[j]][i] < min){
            min = dist[sol[j]][i];
            *cnt = 1; // se cambia min lo si riporta a 1
        } else if(dist[sol[j]][i] == min){
            (*cnt)++; // se non cambia min lo si aumenta
        }
    }
    return min;
}

static int calcolaValore(int *sol, int max_stazioni, int *pop, int N, int **dist){
    int pop_i;
    int dist_min;
    int cnt = 0; // cnt è il numero della distanza a distanza minima da quella calcolata al momento
    int val = 0;

    for (int i = 0; i < N; i++) {
        pop_i = pop[i];
        dist_min = calcolaDistMin(sol, dist, max_stazioni, i, &cnt);
        val += (pop_i * dist_min) / cnt;
    }
    return val;
}

static void disp_rip(int pos, int start, int *sol, int *bestSol, int **dist, int *pop, int max_stazioni, int *stazComuni, int N){
    int val, val_min;

    if(pos >= max_stazioni){
        // calcolo del valore e controllare se è minimo rispetto a quello minimo attuale
        val = calcolaValore(sol, max_stazioni, pop, N, dist);
        val_min = calcolaValore(bestSol, max_stazioni, pop, N, dist);
        if(val < val_min){
            for (int i = 0; i < max_stazioni; i++) {
                bestSol[i] = sol[i];
            }
        }
        return;
    }


    for (int i = start; i < N; i++) {
        if(stazComuni[i] > 0){
            stazComuni[i]--;
            sol[pos] = i;
            disp_rip(pos+1, start, sol, bestSol, dist, pop, max_stazioni, stazComuni, N);
            start++;
            stazComuni[i]++;
        }
    }
}

void obiettivo_two(int **dist, int N, int max_stazioni, int *pop){
    int stazComuni[] = {1, 1, 4, 3, 2};
    int pos = 0;
    int start = 0;

    int *sol = calloc(N, sizeof(int));
    int *bestSol = calloc(N, sizeof(int));

    disp_rip(pos, start, sol, bestSol, dist, pop, max_stazioni, stazComuni, N);

    printf("Soluzione sol: (");
    for (int i = 0; i < max_stazioni; i++) {
        printf(" %d ", bestSol[i]);
    }
    printf(")");

    free(sol);
    free(bestSol);
}