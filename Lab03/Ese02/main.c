#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LUNGHEZZA_CANZONE 256

typedef  struct {
    char **scelte;
    int n_scelte;
} Livello;

/* PROTOTIPI */
void leggi_file(char *filename, int *n_amici, Livello **val, char ***sol);
int princ_molt(int pos, Livello *val, char **sol, int n, int cnt);
void free2d(char **sol, int n_amici);

int main() {
    /* DICHIARAZIONE */
    int n_amici, cnt, pos;
    Livello *val;
    char **sol;

    cnt = pos = 0;

    leggi_file("brani.txt", &n_amici, &val, &sol);

    /* STAMPA POSSIBILI PLAYLIST CON PRINCIPIO DI MOLTIPLICAZIONE */
    cnt = princ_molt(pos, val, sol, n_amici, cnt);

    /* DEALLOCAZIONE */
    free2d(sol, n_amici);
    free(val->scelte);
    free(val);

    return 0;
}

void leggi_file(char *filename, int *n_amici, Livello **_val, char ***_sol) {
    Livello *val;
    char **sol;

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Errore apertura file");
        exit(0);
    }

    fscanf(file, "%d", n_amici);

    val = (Livello *) malloc((*n_amici) * sizeof(Livello));

    for (int i = 0; i < (*n_amici); i++) {
        fscanf(file,"%d", &val[i].n_scelte);
        val[i].scelte = (char **) malloc(val[i].n_scelte * sizeof(char *));
        for(int j = 0; j < val[i].n_scelte; j++){
            val[i].scelte[j]= (char *) malloc(MAX_LUNGHEZZA_CANZONE * sizeof(char));
            fscanf(file,"%s", val[i].scelte[j]);
        }
    }

    sol = (char **) malloc((*n_amici) * sizeof(char *));
    for (int i = 0; i < (*n_amici); ++i) {
        sol[i] = (char *) malloc(MAX_LUNGHEZZA_CANZONE * sizeof (char));
    }

    // Passaggio by pointer
    *_val = val;
    *_sol = sol;

    fclose(file);
}

int princ_molt(int pos, Livello *val, char **sol, int n, int cnt){
    if(pos >= n){
        printf("Playlist %d ", cnt);
        for (int i = 0; i < n; i++) {
            printf(" %s ", sol[i]);
        }
        printf("\n");
        return cnt+1;
    }
    for (int i = 0; i < val[pos].n_scelte; i++) {
        sol[pos] = val[pos].scelte[i];
        cnt = princ_molt(pos+1, val, sol, n, cnt);
    }
    return cnt;
}

void free2d(char **sol, int n_amici) {
    for (int i = 0; i < n_amici; ++i) {
        free(sol[i]);
    }
    free(sol);
}
