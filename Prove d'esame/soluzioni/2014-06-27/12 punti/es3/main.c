#include <stdio.h>
#include <stdlib.h>

#define N 3 // numero di portate

void build_menu(char **data[]);
void pricipioMolt(int pos, char **data[], char **sol);

int main() {

    /*
     * CONSEGNA:
     * Un ristorante serve un menù a prezzo fisso composto da n portate.
     * Per ciascuna portata, il cliente sceglie obbligatoriamente un piatto tra un certo numero di piatti disponibili.
     * Le informazioni sono memorizzate in un vettore data di n elementi, ciascuno dei quali è un puntatore a un vettore di puntatori a stringhe.
     * Quest’ultimo vettore elenca i piatti disponibili per una certa portata.
     * Il numero di questi piatti per portata non è dato esplicitamente, ma quando l’elemento contiene un puntatore a NULL, l’elenco dei piatti di quella portata si considera terminato.
     * Ogni stringa rappresenta un piatto disponibile.
     */

    char ***data;

    data = (char ***) malloc(sizeof(char **) * N);

    for (int i = 0; i < N; i++) {
        data[i] = (char **) malloc(sizeof (char *) * (2*N));
        for (int j = 0; j < (2*N); ++j) {
            data[i][j] = NULL;
        }
    }

    data[0][0] = "Pasta";
    data[0][1] = "Riso";

    data[1][0] = "Carne";
    data[1][1] = "Pesce";
    data[1][2] = "Formaggio";

    data[2][0] = "Gelato";
    data[2][1] = "Torta";

    build_menu(data);

    for (int i = 0; i < N; i++) {
        free(data[i]);
    }
    free(data);
    return 0;
}

void pricipioMolt(int pos, char **data[], char **sol){
    if(pos >= N){
        for (int i = 0; i < N; i++) {
            printf("%s ", sol[i]);
        }
        printf("\n");
        return;
    }

    for (int i = 0; i < (2*N); ++i) {
        if(data[pos][i] != NULL){
            sol[pos] = data[pos][i];
            pricipioMolt(pos+1, data, sol);
        } else return;
    }
}

void build_menu(char **data[]){
    int pos = 0;

    char **sol = malloc(sizeof(char *)* N);
    pricipioMolt(pos, data, sol);

    free(sol);
}