#include <stdio.h>
#include <math.h>
#include <stdlib.h>

#define N 4
#define M 3

int minmaxdiff(int **A, int n, int m);

int main() {
    int index;
    int **A;

    A = malloc(sizeof(int)*N);
    for (int i = 0; i < N; i++) {
        A[i] = malloc(sizeof (int)*M);
    }
    index = -1;

    printf("Inserisci i valori\n");
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < M; j++) {
            printf("A[%d][%d]=", i, j);
            scanf("%d", &A[i][j]);
        }
    }

    index = minmaxdiff(A, N, M);
    if (index != -1){
        printf("L'indice della colonna risultante vale: %d", index);
    } else {
        printf("Errore!");
    }

    return 0;
}

int minmaxdiff(int **A, int n, int m){
    int index;
    int sum;
    int *bestDiff;

    bestDiff = malloc(sizeof(int) * m);
    for (int i = 0; i < m; i++) {
        bestDiff[i] = -1;
    }

    for (int j = 0; j < m; j++){
        sum = A[0][j];
        for (int i = 1; i < n; i++){
            sum -= A[i][j];
            if (abs(sum) > bestDiff[j]){
                bestDiff[j] = abs(sum);
            }
            sum = A[i][j];
        }
    }

    sum = 1000;

    for (int i = 0; i < m; i++){
        if(bestDiff[i] < sum){
            sum = bestDiff[i];
            index = i;
        }
    }

    free(bestDiff);
    return index;
}
