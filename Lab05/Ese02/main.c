#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// TYPEDEF
typedef struct
{
    char color1;
    int value1;
    char color2;
    int value2;
} Tile;

typedef struct
{
    int id;
    int rotation;
} Cell;

// PROTOTIPI
void read_file(char *filename, char *filename2, Tile **tiles, Cell **boards, int *t, int *r, int *c);

void stampa_tiles(Tile *tiles, int t);
void stampa_boards(Cell *boards, int r, int c);

int main()
{
    // DICHIARAZIONE
    int r, c; // Righe R X C Colonne (matrice boards)
    int t;    // Tessere del gioco

    Tile *tiles;
    Cell *boards;

    read_file("tiles.txt", "board.txt", &tiles, &boards, &t, &r, &c); 

    stampa_tiles(tiles, t);
    stampa_boards(boards, r, c);

    // USO DISPOSIZIONI RIPETUTE, guardare le slide del sudoku

    free(tiles);
    free(boards);

    return 0;
}

// FUNCTIONS
void read_file(char *filename, char *filename2, Tile **tiles, Cell **boards, int *t, int *r, int *c)
{
    FILE *fin;

    fin = fopen(filename, "r");
    if (fin == NULL)
    {
        printf("Errore nella lettura del file!");
        exit(1);
    }

    fscanf(fin, "%d\n", t);
    *tiles = (Tile *)malloc((*t) * sizeof(Tile));

    for (int i = 0; i < *t; i++)
    {
        fscanf(fin, "%c %d %c %d\n", &(*tiles)[i].color1, &(*tiles)[i].value1, &(*tiles)[i].color2, &(*tiles)[i].value2);
    }

    fclose(fin);

    fin = fopen(filename2, "r");
    if (fin == NULL)
    {
        printf("Errore nella lettura del file!");
        exit(1);
    }

    fscanf(fin, "%d %d", r, c);
    *boards = (Cell *)malloc((*r) * (*c) * sizeof(Cell));

    for (int i = 0; i < (*r) * (*c); i++) // TODO: gestire la rotazione
    {
        fscanf(fin, "%d %d\n", &(*boards)[i].id, &(*boards)[i].rotation);
    }

    fclose(fin);
}

void stampa_tiles(Tile *tiles, int t)
{
    for (int i = 0; i < t; i++)
    {
        printf("%c %d %c %d\n", tiles[i].color1, tiles[i].value1, tiles[i].color2, tiles[i].value2);
    }
}

void stampa_boards(Cell *boards, int r, int c)
{
    for (int i = 0; i < r * c; i++)
    {
        printf("%d %d\n", boards[i].id, boards[i].rotation);
    }
}