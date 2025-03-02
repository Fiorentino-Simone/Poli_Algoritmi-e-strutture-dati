#include <stdio.h>
#include <limits.h>

#define N 7

void sottovettoriMaxSum(int v[N]);

int main() {
    int v[N] = {-1, 2, 3, -6, 1, 3, 1};

    sottovettoriMaxSum(v);

    return 0;
}

void sottovettoriMaxSum(int v[N]){
    int max_sum = INT_MIN;
    int start = 0, end = 0;
    int temp_start = 0;
    int current_sum = 0;

    // Algoritmo di Kadane modificato
    for (int i = 0; i < N; i++) {
        if (current_sum <= 0) {
            temp_start = i;
            current_sum = v[i];
        } else {
            current_sum += v[i];
        }

        if (current_sum > max_sum && (i - temp_start + 1 < N)) { // Evita di prendere tutto il vettore
            max_sum = current_sum;
            start = temp_start;
            end = i;
        }
    }

    // Stampa del risultato
    printf("Sottovettore con somma massima: ");
    for (int i = start; i <= end; i++) {
        printf("%d ", v[i]);
    }
    printf("\nSomma massima: %d\n", max_sum);
}