#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_AMICI 10
#define MAX_CANZONI 5
#define MAX_LUNGHEZZA_CANZONE 256

// Struttura per memorizzare le canzoni proposte da ciascun amico
char canzoni[MAX_AMICI][MAX_CANZONI][MAX_LUNGHEZZA_CANZONE];
int numero_canzoni[MAX_AMICI];
int A; // Numero di amici

// Funzione per leggere i dati dal file
void leggi_file(const char *nome_file) {
    FILE *file = fopen(nome_file, "r");
    if (!file) {
        perror("Errore apertura file");
        exit(1);
    }

    // Leggiamo il numero di amici
    fscanf(file, "%d", &A);

    // Per ogni amico, leggiamo il numero di canzoni e i titoli delle canzoni
    for (int i = 0; i < A; i++) {
        fscanf(file, "%d", &numero_canzoni[i]);
        for (int j = 0; j < numero_canzoni[i]; j++) {
            fscanf(file, "%s", canzoni[i][j]);
        }
    }

    fclose(file);
}

// Funzione ricorsiva per generare le playlist
void genera_playlist(int amico, char playlist_corrente[MAX_AMICI][MAX_LUNGHEZZA_CANZONE]) {
    // Caso base: se abbiamo scelto una canzone per ogni amico, stampiamo la playlist
    if (amico == A) {
        printf("Playlist: ");
        for (int i = 0; i < A; i++) {
            printf("%s ", playlist_corrente[i]);
        }
        printf("\n");
        return;
    }

    // Passo ricorsivo: scegliamo una canzone per l'amico corrente
    for (int i = 0; i < numero_canzoni[amico]; i++) {
        strcpy(playlist_corrente[amico], canzoni[amico][i]);
        genera_playlist(amico + 1, playlist_corrente);
    }
}

int main() {
    leggi_file("brani.txt");

    // Array temporaneo per costruire la playlist corrente
    char playlist_corrente[MAX_AMICI][MAX_LUNGHEZZA_CANZONE];

    // Generiamo tutte le playlist possibili
    genera_playlist(0, playlist_corrente);

    return 0;
}
