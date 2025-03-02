#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int **tessere;
    int NR, NC;
} Griglia;

typedef struct{
    int i, j;
} Mossa;

typedef struct {
    Mossa *mosse;
    int nMosse;
} Mosse;

void GRIDprint(Griglia g);
int GRIDcheck(char *filename, Griglia g);
void GRIDsolve(Griglia g);

int main() {
    FILE *fin;
    int NR, NC;
    Griglia grid;
    int cambiDirezione = 0;

    fin = fopen("griglia.txt", "r");
    if(fin == NULL){
        printf("Errore nella lettura del file!");
        exit(-1);
    }

    fscanf(fin, "%d %d", &NR, &NC);
    grid.tessere = malloc(sizeof(int*) * NR);
    for (int i = 0; i < NR; i++) {
        grid.tessere[i] = malloc(sizeof(int)*NC);
    }

    for (int i = 0; i < NR; i++) {
        for (int j = 0; j < NC; j++) {
            fscanf(fin, "%d", &grid.tessere[i][j]);
        }
    }
    grid.NC = NC;
    grid.NR = NR;


    // problema di verifica
    if((cambiDirezione = GRIDcheck("proposta.txt", grid))){
        printf("La soluzione passata risulta valida!");
        printf("\n");
        printf("I cambi direzione calcolati sono: %d", cambiDirezione);
    } else {
        printf("La soluzione passata risulta NON valida!");
    }

    // problema di ottimizzazione
    GRIDsolve(grid);

    return 0;
}

// FUNCTION
void GRIDprint(Griglia g){
    printf("\n");
    for (int i = 0; i < g.NR; i++) {
        for (int j = 0; j < g.NC; j++) {
            printf(" %d ", g.tessere[i][j]);
        }
        printf("\n");
    }
}

static int calcolaCelleBianche(Griglia g){
    int cnt = 0;
    for (int i = 0; i < g.NR; i++) {
        for (int j = 0; j < g.NC; j++) {
            if(g.tessere[i][j] == 0){
                cnt++;
            }
        }
    }
    return cnt;
}

static int checkIfNera(Mossa mossa, Griglia g){
    for (int i = 0; i < g.NR; i++) {
        for (int j = 0; j < g.NC; j++) {
            if(g.tessere[i][j] == 1){
                // se la cella è nera controllo che la mossa lo sia
                if(i == mossa.i && j == mossa.j){
                    return 1;
                }
            }
        }
    }
    return 0;
}

static int cambiDirezione(Mosse mosse){
    int cambiDirezione = 0;
    char direzione;

    if((mosse.mosse[1].j == mosse.mosse[0].j) && (mosse.mosse[1].i != mosse.mosse[0].i)){
        // ti stai muovendo a NORD o a SUD
        direzione = 'j';
    } else if((mosse.mosse[1].j != mosse.mosse[0].j) && (mosse.mosse[1].i == mosse.mosse[0].i)) {
        // ti stai muovendo a OVEST o a EST
        direzione = 'i';
    }

    for (int i = 1; i < mosse.nMosse; i++) {
        if((mosse.mosse[i].j == mosse.mosse[i-1].j) && (mosse.mosse[i].i != mosse.mosse[i-1].i)){
            // ti stai muovendo a NORD o a SUD
            if(direzione == 'i'){
                cambiDirezione++;
            }
            direzione = 'j';
        } else if((mosse.mosse[i].j != mosse.mosse[i-1].j) && (mosse.mosse[i].i == mosse.mosse[i-1].i)) {
            // ti stai muovendo a OVEST o a EST
            if(direzione == 'j'){
                // prima eri a NORD o a SUD
                cambiDirezione++;
            }
            direzione = 'i';
        }
    }

    return cambiDirezione;
}

static int checkIsValid(Mosse mosse, Griglia g, int nMosse){
    if(mosse.mosse[0].i != 0 || mosse.mosse[0].j != 0){
        //printf("La cella iniziale non è [0,0]\n");
        return 0;
    }

    for (int i = 0; i < nMosse; i++) {
        if(checkIfNera(mosse.mosse[i], g)){
            //printf("La cella (%d, %d) risulta nera!\n", mosse.mosse[i].i, mosse.mosse[i].j);
            return 0;
        }
    }

    // bisogna calcolare il numero di cambi direzione
    return cambiDirezione(mosse);
}

int GRIDcheck(char *filename, Griglia g){
    FILE *fin;
    int celleBianche = 0;
    int nMosse = 0;
    Mosse mosse;

    fin = fopen(filename, "r");
    if(fin == NULL){
        printf("Errore nell'apertura del file!");
        exit(-1);
    }

    // il file è cosi composto:
    // nella prima riga è presente il numero di mosse fatte
    // seguono n-mosse righe con la tessera selezionata (i,j)


    fscanf(fin, "%d", &nMosse);
    celleBianche = calcolaCelleBianche(g);

    // se le celle bianche non sono uguali alle mosse esci:
    // ho sono meno celle quindi non le ha visitate tutte
    // ho sono più celle quindi ci sono duplicati o celle nere
    if (celleBianche != nMosse){
        printf("Le celle attraversate NON sono tutte!\n");
        return 0;
    }
    mosse.nMosse = nMosse;
    mosse.mosse = malloc(nMosse*sizeof(Mossa));
    // dato una lista di celle bisogna controllare:
    // che non ci siano celle nere fra di loro
    for (int i = 0; i < nMosse; i++) {
        fscanf(fin, "%d %d", &mosse.mosse[i].i, &mosse.mosse[i].j);
    }

    return checkIsValid(mosse, g, nMosse);
}

int di[] = {-1, 1, 0, 0}; // Spostamenti nelle righe
int dj[] = {0, 0, -1, 1}; // Spostamenti nelle colonne

int isValid(int i, int j, Griglia g, int **visited) {
    /*
     * La funzione restituisce 1 (vero) se la cella è valida, cioè:
        È dentro i limiti della griglia.
        È una cella bianca.
        Non è già stata visitata.
        Restituisce 0 (falso) altrimenti.
     */
    return (i >= 0 && i < g.NR && j >= 0 && j < g.NC && g.tessere[i][j] == 0 && !visited[i][j]);
}

void DFS(Griglia g, int i, int j, int dir, int **visited, int *minCambi, int cambi, int celleCoperte, int totalBianche) {
    if (celleCoperte == totalBianche) {
        if (cambi < *minCambi) {
            *minCambi = cambi;
        }
        return;
    }

    visited[i][j] = 1;
    for (int d = 0; d < 4; d++) {
        int ni = i + di[d];
        int nj = j + dj[d];
        if (isValid(ni, nj, g, visited)) {
            DFS(g, ni, nj, d, visited, minCambi, cambi + (d != dir), celleCoperte + 1, totalBianche);
        }
    }
    visited[i][j] = 0;
}

void GRIDsolve(Griglia g) {
    int totalBianche = 0;
    for (int i = 0; i < g.NR; i++) {
        for (int j = 0; j < g.NC; j++) {
            if (g.tessere[i][j] == 0) {
                totalBianche++;
            }
        }
    }

    int **visited = malloc(g.NR * sizeof(int *));
    for (int i = 0; i < g.NR; i++) {
        visited[i] = calloc(g.NC, sizeof(int));
    }

    int minCambi = 100000;
    DFS(g, 0, 0, -1, visited, &minCambi, -1, 1, totalBianche);

    printf("\nIl numero minimo di cambi di direzione vale: %d\n", minCambi);

    for (int i = 0; i < g.NR; i++) {
        free(visited[i]);
    }
    free(visited);
}