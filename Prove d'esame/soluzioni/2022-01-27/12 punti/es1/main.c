#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

#define r 3
#define c 4

void f(int M[r][c], int ***matr_new, int *r_new, int *c_new);

int main() {
    int M[r][c] = {
            1,2,3,8,
            6,12,0,3,
            0,2,5,3
    };
    int **matr_new;
    int r_new, c_new;


    r_new = c_new = 0;

    f(M, &matr_new, &r_new, &c_new);

    printf("Matrice originale: ");
    printf("\n");
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            printf(" matr[%d][%d] = %d ", i, j, M[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    printf("Matrice modificata: ");
    printf("\n");
    for (int i = 0; i < r_new; i++) {
        for (int j = 0; j < c_new; j++) {
            printf(" matr_new[%d][%d] = %d ", i, j, matr_new[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    return 0;
}

static int check(int *righe, int *colonne, int i ,int j){
    int exit = 1;
    for (int k = 0; k < r; k++) {
        if(righe[k] == i) {
            exit = 0;
        }
    }
    for (int k = 0; k < c; k++) {
        if(colonne[k] == j) {
            exit = 0;
        }
    }
    return exit;
}

static int check2(int *righe, int *colonne, int i, int j){
    for (int k = 0; k < r; k++) {
        if(righe[k] == i){
            return 1;
        }
    }
    for (int k = 0; k < c; k++) {
        if(colonne[k] == j){
            return 1;
        }
    }
    return 0;
}

void f(int M[r][c], int ***matr_new, int *r_new, int *c_new){
    int **M_primo;
    int *righe, *colonne, *elementi;
    int k = 0, l = 0;

    righe = calloc(r, sizeof(int));
    colonne = calloc(c, sizeof(int));
    for (int i = 0; i < r; i++) {
        righe[i] = -1;
    }
    for (int i = 0; i < c; i++) {
        colonne[i] = -1;
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if(M[i][j] == 0 && check(righe, colonne, i ,j)){
                righe[k] = i;
                colonne[k] = j;
                k++;
            }
        }
    }

    *r_new = r-k;
    *c_new = c-k;
    elementi = malloc(sizeof(int) * (*r_new) * (*c_new));

    M_primo = malloc(sizeof(int) * (*r_new));
    for (int i = 0; i < *r_new; i++) {
        M_primo[i] = malloc(sizeof(int)*(*c_new));
    }

    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            if(!check2(righe, colonne, i, j)){
                elementi[l++] = M[i][j];
            }
        }
    }

    l = 0;
    for (int i = 0; i < *r_new; i++) {
        for (int j = 0; j < *c_new; j++) {
            M_primo[i][j] = elementi[l++];
        }
    }

    *matr_new = M_primo;
}

