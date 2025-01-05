#include <stdio.h>
#include <stdlib.h>

// PROTOTIPI
int conta_occorrenze(int *a, int n, int candidato);
int trova_candidato(int *a, int l, int r);
int majority(int *a, int n);

void stampa_vet(int *a, int n);

int main() {
    int scelta;
    int *vect;
    int n, result;

    printf("Digita 1 se vuoi inserire i dati manualmente oppure 2 se vuoi usare i dati di mock: ");
    scanf("%d", &scelta);
    printf("\n");
    if(scelta == 1){
        int dim;
        printf("Inserisci la dimensione del vettore: ");
        scanf("%d", &dim);

        vect = (int *) malloc(sizeof (int) * dim);
        for (int i = 0; i < dim; i++){
            printf("Inserisci l'elemento %d: ", (i+1));
            scanf("%d", &vect[i]);
        }

        result = majority(vect, dim);
        if(result == -1){
            printf("Non esiste l'elemento maggioritario");
        } else {
            printf("Elemento maggioritario del vettore e': %d", result);
        }
    } else if (scelta == 2) {
        int vect1[] = {3, 3, 9, 4, 3, 5, 3};
        n = 7;
        stampa_vet(vect1, n);
        result = majority(vect1, n);
        if(result == -1){
            printf("Non esiste l'elemento maggioritario nel vettore 1");
        } else {
            printf("Elemento maggioritario del vettore 1 e': %d", result);
        }
        printf("\n");

        int vect2[] = {0, 1, 0, 2, 3, 4, 0, 5};
        n = 8;
        stampa_vet(vect2, n);
        result = majority(vect2, n);
        if(result == -1){
            printf("Non esiste l'elemento maggioritario nel vettore 2");
        } else {
            printf("Elemento maggioritario del vettore 2 e': %d", result);
        }
    }
    return 0;
}

// FUNCTIONS
int majority(int *a, int n) {
    int candidato = trova_candidato(a, 0, n - 1);

    int occorrenze = conta_occorrenze(a, n, candidato);
    if (occorrenze > n / 2) {
        return candidato;
    } else {
        return -1;
    }
}

// FUNZIONE RICORSIVA
int trova_candidato(int *a, int l, int r) {
    // Caso di terminazione: vettore unitario
    if (l == r) {
        return a[l];
    }

    int m = (l + r) / 2;
    int candidato_sx = trova_candidato(a, l, m);
    int candidato_dx = trova_candidato(a, m + 1, r);

    if (candidato_sx == candidato_dx) {
        return candidato_sx;
    }

    int count_sx = conta_occorrenze(a + l, r - l + 1, candidato_sx);
    int count_dx = conta_occorrenze(a + l, r - l + 1, candidato_dx);

    // Restituisco il candidato del sottovettore di sinistra se solo maggiore le occorrenze di sinistra, sennò vicerversa
    return count_sx > count_dx ? candidato_sx : candidato_dx;
}


int conta_occorrenze(int *a, int n, int candidato) {
    int count = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] == candidato) {
            count++;
        }
    }
    return count;
}

void stampa_vet(int *a, int n){
    for (int i = 0; i < n; ++i) {
        printf(" %d ", a[i]);
    }
    printf("\n");
}
