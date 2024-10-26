#include <stdio.h>
#include <stdlib.h>

/* PROTOTIPI */
int conta_occurrence(int *a, int N, int candidate);
int trova_candidato(int *a, int start, int end);
int majority(int *a, int N);

int main() {
    int scelta;
    int *vect;
    int n, result;

    printf("Digita 1 se vuoi inserire i dati manualmente oppure 2 se vuoi usare i dati moccati: ");
    scanf("%d", &scelta);
    if(scelta == 2){
        int vet1[] = {3, 3, 9, 4, 3, 5, 3};
        n = 7;
        result = majority(vet1, n);
        printf("Elemento maggioritario (vet1): %d\n", result);

        int vet2[] = {0, 1, 0, 2, 3, 4, 0, 5};
        n = 8;
        result = majority(vet2, n);
        printf("Elemento maggioritario (vet2): %d\n", result);
    } else {
        int dim;
        printf("Inserisci la dimensione di vect: ");
        scanf("%d", &dim);

        vect = (int *) malloc(sizeof (int) * dim);
        for (int i = 0; i < dim; i++){
            printf("Inserisci l'elemento %d: ", (i+1));
            scanf("%d", &vect[i]);
        }

        result = majority(vect, dim);
        printf("Elemento maggioritario del vettore: %d", result);
    }
    return 0;
}

// Funzione per contare le occorrenze di un elemento in un intervallo dell'array
int conta_occurrence(int *a, int N, int candidato) {
    int count = 0;
    for (int i = 0; i < N; i++) {
        if (a[i] == candidato) {
            count++;
        }
    }
    return count;
}

// FUNZIONE RICORSIVA
int trova_candidato(int *a, int start, int end) {
    // Caso di terminazione: vettore unitario
    if (start == end) {
        return a[start];
    }

    int centro = (start + end) / 2;
    int candidato_sinistro = trova_candidato(a, start, centro);
    int candidato_destro = trova_candidato(a, centro + 1, end);

    // Se i due candidati sono uguali, lo restituiamo
    if (candidato_sinistro == candidato_destro) {
        return candidato_sinistro;
    }

    // Se sono diversi, contiamo le occorrenze per ciascuno
    int count_sinistro = conta_occurrence(a + start, end - start + 1, candidato_sinistro);
    int count_destro = conta_occurrence(a + start, end - start + 1, candidato_destro);

    // Restituiamo il candidato che ha la maggioranza in questo intervallo
    return count_sinistro > count_destro ? candidato_sinistro : candidato_destro;
}

int majority(int *a, int N) {
    // Troviamo il candidato maggioritario usando la ricorsione
    int candidato = trova_candidato(a, 0, N - 1);

    int occorrenze = conta_occurrence(a, N, candidato);
    if (occorrenze > N / 2) {
        return candidato;
    } else {
        return -1;
    }
}