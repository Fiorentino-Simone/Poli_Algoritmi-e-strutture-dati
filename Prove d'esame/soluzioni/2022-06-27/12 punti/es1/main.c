#include <stdio.h>
#include <stdlib.h>

#define D 2
#define R 3
#define C 3

void flatter(int M[D*D][R][C]);

int main() {

    int M[D*D][R][C] = {
            {18,19,20,9,10,11,0,1,2},
            {12,13,14,6,7,8,0,1,2},
            {6,7,8,3,4,5,0,1,2},
            {0,1,2,0,1,2,0,1,2}
    };

    flatter(M);

    return 0;
}

void flatter(int M[D*D][R][C]){
    int **M_new;

    M_new = malloc(sizeof(int *) * (D*R));
    for (int i = 0; i < (D*R); i++) {
        M_new[i] = malloc(sizeof(int) * (D*C));
    }

    for (int i = 0; i < D * D; i++) { // Scorriamo i livelli
        int rowBlock = (i / D) * R; // Determina il blocco di righe
        int colBlock = (i % D) * C; // Determina il blocco di colonne

        for (int r = 0; r < R; r++) {
            for (int c = 0; c < C; c++) {
                M_new[rowBlock + r][colBlock + c] = M[i][r][c];
            }
        }
    }

    printf("\n");
    for (int i = 0; i < D*R; i++) {
        for (int j = 0; j < D*C; j++) {
            printf(" %d ", M_new[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
