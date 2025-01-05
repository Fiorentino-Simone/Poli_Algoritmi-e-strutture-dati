#include <stdio.h>
#include <stdlib.h>

/* PROTOTIPI */
int **malloc2dR(int nr, int nc);
void malloc2dP(int ***matr, int nr, int nc);
void free2d(int **matr, int nr);

void stampa_vect(int *vect, int n);

void separa(int **matr, int nr, int nc, int **caselle_nere, int **caselle_bianche);

int main() {
    /* DICHIARAZIONE */
    FILE *fin;
    int nr, nc, b, n;
    int **matr;
    int *caselle_nere, *caselle_bianche;

    fin = fopen("mat.txt", "r");
    if(fin == NULL){
        printf("Errore nell'apertura del file!");
        exit(1);
    }
    fscanf(fin, "%d %d", &nr, &nc);

    /* ALLOCAZIONE DINAMICA */
    // matr = malloc2dR(nr, nc);
    malloc2dP(&matr, nr, nc);

    for (int i = 0; i<nr; i++){
        for (int j = 0; j < nc; j++) {
            fscanf(fin, "%d", &matr[i][j]);
        }
    }

    separa(matr, nr, nc, &caselle_nere, &caselle_bianche);

    // Gestione lunghezza vettori caselle_nere e caselle_bianche
    n = b = ((nr*nc) / 2);
    if((nr*nc) % 2 != 0){
        b++;
    }

    printf("Stampa del vettore delle caselle nere: \n");
    stampa_vect(caselle_nere, n);
    printf("\n");
    printf("Stampa del vettore delle caselle bianche: \n");
    stampa_vect(caselle_bianche, b);

    /* DEALLOCAZIONE DINAMICA */
    free2d(matr, nr);
    free(caselle_nere);
    free(caselle_bianche);
    fclose(fin);

    return 0;
}

/* FUNCTIONS */
int **malloc2dR(int nr, int nc){
    int **matr;
    matr = (int **) malloc(nr * sizeof(int *));
    for (int i = 0; i<nr; i++){
        matr[i] = (int *) malloc(nc * sizeof(int));
    }
    return matr;
}

void malloc2dP(int ***_matr, int nr, int nc){
    int **matr;

    matr = (int **) malloc(nr * sizeof(int *));
    for (int i = 0; i<nr; i++){
        matr[i] = (int *) malloc(nc * sizeof(int));
    }

    *_matr = matr;
}

void free2d(int **matr, int nr){
    for(int i = 0; i<nr; i++){
        free(matr[i]);
    }
    free(matr);
}

void stampa_vect(int *matr, int n){
    for (int i = 0; i<n; i++){
        printf(" %d ", matr[i]);
    }
}

void separa(int **matr, int nr, int nc, int **caselle_nere, int **caselle_bianche){
    int *c_nere, *c_bianche;
    int b, n;
    int valori;
    int max_value = nr * nc;

    n = b = (max_value / 2);
    if(max_value % 2 != 0){
        b++;
    }

    c_nere = (int *) malloc(n * sizeof(int));
    c_bianche = (int *) malloc(b * sizeof(int));

    n = b = valori = 0;

    for (int i = 0; i<nr; i++){
        for (int j = 0; j<nc; j++){
            if(valori % 2 == 0){
                c_bianche[b++] = matr[i][j];
            }
            else {
                c_nere[n++] = matr[i][j];
            }
            valori++;
        }
    }

    *caselle_nere = c_nere;
    *caselle_bianche = c_bianche;
}

