#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TYPEDEF
typedef struct {
    char color1, color2;
    int value1, value2;
} Tile;

typedef struct {
    int id;
    int rotation;
} Cell;

// PROTOTIPI
void read_file(char *filename, char *filename2, Tile **tiles, Cell **boards, int *t, int *r, int *c);

int main() {
    // DICHIARAZIONE
    int r, c; // Righe R X C Colonne (matrice boards)
    int t; // Tessere del gioco

    Tile *tiles;
    Cell *boards;

    read_file("tiles.txt", "board.txt", &tiles, &boards, &t, &r, &c); //TODO: non funziona la lettura
    // USO DISPOSIZIONI RIPETUTE, guardare le slide del sudoku

    free(tiles);
    free(boards);

    return 0;
}

// FUNCTIONS
void read_file(char *filename, char *filename2, Tile **tiles, Cell **boards, int *t, int *r, int *c){
    FILE *fin;

    fin = fopen("tiles.txt", "r");
    if(fin == NULL){
        printf("Errore nella lettura del file!");
        exit(1);
    }

    fscanf(fin, "%d", t);
    *tiles = (Tile *) malloc((*t) * sizeof(Tile));

    for (int i = 0; i < (*t); i++) {
        fscanf(fin, "%c %d %c %d", &((*tiles)[i].color1), &((*tiles)[i].value1), &((*tiles)[i].color2), &((*tiles)[i].value2));
    }

    for (int i = 0; i < (*t); i++) {
        printf("%c %d %c %d", ((*tiles)[i].color1), ((*tiles)[i].value1), ((*tiles)[i].color2), ((*tiles)[i].value2));
        printf("\n");
    }

    fclose(fin);
}