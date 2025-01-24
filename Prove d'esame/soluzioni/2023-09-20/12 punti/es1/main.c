#include <stdio.h>
#include <stdlib.h>

#define R 5
#define C 4

void printfMatr(int M[R][C]);
void f(int M[R][C], int k, int ***new_M);

int main() {
    int M[R][C] = {
            1, 2, 3, 4,
            2, 3, -2, 5,
            1, 2, 3, 4,
            -2, -3, -1, 0,
            -5, 1, -2, 9
    };

    int **new_M;

    int k = 2;

    printfMatr(M);

    f(M, k, &new_M);

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            printf("M'[%d][%d] = %d\n", i, j, new_M[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    return 0;
}

void printfMatr(int M[R][C]){
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            printf("M[%d][%d] = %d\n", i, j, M[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void f(int M[R][C], int k, int ***new_M){
    int sum;
    int cnt;

    (*new_M) = malloc(sizeof(int*) * R);
    for (int i = 0; i < R; i++) {
        (*new_M)[i] = malloc(sizeof (int)* C);
    }

    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            sum = 0;
            cnt = 0;

            // RIGA
            // uso for discendente su RIGA
            for (int w = j-1; cnt < k; w--, cnt++) {
                if(w < 0){
                    // se il valore supera i limiti della matrice
                    break;
                }
                sum += M[i][w];
            }
            cnt = 0;
            // uso for ascendente su RIGA
            for (int w = j+1; cnt < k; w++, cnt++) {
                if(w >= C){
                    // se il valore supera i limiti della matrice
                    break;
                }
                sum += M[i][w];
            }
            cnt = 0;

            // COLONNA
            // uso for discendente su COLONNA
            for (int w = i-1; cnt < k; w--, cnt++) {
                if(w < 0){
                    // se il valore supera i limiti della matrice
                    break;
                }
                sum += M[w][j];
            }
            cnt = 0;
            // uso for ascendente su COLONNA
            for (int w = i+1; cnt < k; w++, cnt++) {
                if(w >= R){
                    // se il valore supera i limiti della matrice
                    break;
                }
                sum += M[w][j];
            }

            (*new_M)[i][j] = sum;
        }
    }
}