#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXL 3

typedef struct {
    char val[MAXL];
} Token;

typedef struct {
    Token **token;
    int NR, NC;
} Grid;

typedef struct {
    Token *token;
    int prize;
    int lun;
} TokenBonus;

typedef struct {
    TokenBonus *tokenBonus;
    int B;
} Bonus;

typedef struct {
    Token token;
    int r, c;
} Tessera;

// GRID
void GRIDprint(Grid G);

// BONUS
void BONUSprint(Bonus b);

int VerificaProposta(char *filename, Grid grid, Bonus bonus);
void ottimizzazione(Grid grid, Bonus bonus);

int main() {
    FILE *fin;
    int N, B;
    int lun, val, sumBonus;
    Grid grid;
    Bonus bonus;

    fin = fopen("grid.txt", "r");
    if(fin == NULL){
        printf("Errore nell'apertura del file!");
        exit(-1);
    }

    fscanf(fin, "%d", &N);
    grid.token = malloc(sizeof(Token *) * N);
    for (int i = 0; i < N; i++) {
        grid.token[i] = malloc(sizeof (Token) * N);
    }
    grid.NC = grid.NR = N;
    for (int i = 0; i < grid.NC; i++) {
        for (int j = 0; j < grid.NR; j++) {
            fscanf(fin, "%s", grid.token[i][j].val);
        }
    }


    fin = fopen("bonus.txt", "r");
    fscanf(fin, "%d", &B);
    bonus.tokenBonus = calloc(B, sizeof(TokenBonus));
    bonus.B = B;
    for (int i = 0; i < B; i++) {
        fscanf(fin, "%d %d", &lun, &val);
        bonus.tokenBonus[i].token = calloc(lun, sizeof(Token));
        for (int j = 0; j < lun; j++) {
            fscanf(fin, "%s", bonus.tokenBonus[i].token[j].val);
        }
        bonus.tokenBonus[i].prize = val;
        bonus.tokenBonus[i].lun = lun;
    }

    // problema di verifica
    if((sumBonus = VerificaProposta("mosse.txt", grid, bonus))){
        printf("La soluzione proposta risulta valida!\n");
        printf("Il valore del bonus risulta: %d", sumBonus);
    } else {
        printf("La soluzione proposta NON risulta valida!");
    }

    // problema di ottimizzazione
    ottimizzazione(grid, bonus);

    return 0;
}

// FUNCTIONS
void GRIDprint(Grid G){
    for (int i = 0; i < G.NC; i++) {
        for (int j = 0; j < G.NR; j++) {
            printf(" %s ", G.token[i][j].val);
        }
    }
}

void BONUSprint(Bonus b){
    fprintf(stdout, " %d \n", b.B);
    for (int i = 0; i < b.B; i++) {
        fprintf(stdout, " %d %d ", b.tokenBonus[i].lun, b.tokenBonus[i].prize);
        for (int j = 0; j < b.tokenBonus[i].lun; j++) {
            fprintf(stdout, " %s ", b.tokenBonus[i].token[j].val);
        }
        printf("\n");
    }
}

static int checkBuffer(Tessera *tessere, Token *buffer, Bonus bonus, Grid grid, int mosse, int **visited){
    int cnt;
    int sum = 0;
    int indice_precedente = -1;
    int errato = 0;

    for (int i = 0; i < mosse; i++) {
        if(visited[tessere[i].r][tessere[i].c] == 0){
            if(i % 2 == 0){
                if(i == 0){
                    if(tessere[i].r != 0){
                        // i = 0 --> per forza deve essere una tessera della riga 0
                        return 0;
                    }
                } else {
                    if(tessere[i].r != tessere[i-1].r){
                        // i > 1 --> scelgo una tessera della riga i data dal passo precedente e colonna j qualsiasi
                        return 0;
                    }
                }
            } else {
                if(tessere[i].c != tessere[i-1].c){
                    // scelgo una tessera della colonna j data dal passo precedente e riga i qualsiasi
                    return 0;
                }
            }
            visited[tessere[i].r][tessere[i].c] = 1;
        } else {
            // la tessera non può essere utilizzata più volte
            return 0;
        }
    }

    // copio tessere nel buffer
    for (int i = 0; i < mosse; i++) {
        strcpy(buffer[i].val, tessere[i].token.val);
    }

    for (int i = 0; i < bonus.B; i++) {
        if(bonus.tokenBonus[i].lun > mosse){
            continue;
        }
        cnt = 0;
        indice_precedente = -1;
        errato = 0;
        if(bonus.tokenBonus[i].lun == mosse){
            for (int j = 0; j < bonus.tokenBonus[i].lun; j++) {
                // se lun == mosse
                if(strcmp(bonus.tokenBonus[i].token[j].val, buffer[j].val) == 0){
                    cnt++;
                }
            }
            if(cnt == mosse){
                sum += bonus.tokenBonus[i].prize;
            }
        }
        else {
            for (int j = 0; j < bonus.tokenBonus[i].lun; j++) {
                for (int k = 0; k < mosse; k++) {
                    if(strcmp(bonus.tokenBonus[i].token[j].val, buffer[k].val) == 0){
                        if(indice_precedente == -1){
                            indice_precedente = k;
                            cnt++;
                        } else {
                            if(k == (indice_precedente + 1)){
                                indice_precedente = k;
                                cnt++;
                            } else{
                                errato = 1;
                                break;
                            }
                        }
                        break;
                    }
                }
                if(errato){
                    break;
                }
            }

            if(!errato && cnt > 1){
                sum += bonus.tokenBonus[i].prize;
            }
        }
    }
    return sum;
}

int VerificaProposta(char *filename, Grid grid, Bonus bonus){
    FILE *fin;
    int mosse;
    Token *buffer;
    Tessera *tessere;

    int **visited = calloc(grid.NR, sizeof (int *));
    for (int i = 0; i < grid.NR; i++) {
        visited[i] = calloc(grid.NC, sizeof (int));
    }

    fin = fopen(filename, "r");
    if(fin == NULL){
        printf("Errore nella lettura del file!");
        exit(-1);
    }

    fscanf(fin, "%d", &mosse);
    tessere = malloc(sizeof(Tessera) * mosse);
    buffer = malloc(sizeof (Token) * mosse);
    for (int i = 0; i < mosse; i++) {
        fscanf(fin, "%s %d %d", tessere[i].token.val, &tessere[i].r, &tessere[i].c);
    }
    fclose(fin);
    return checkBuffer(tessere, buffer, bonus, grid, mosse, visited);
}

void powerset(int pos, int k, Tessera *tessere, Token *buffer, Grid grid, Bonus bonus, int *maxBonus, Tessera *bestSol, int **visited){
    int bonusValue;
    if(pos >= k){
        if((bonusValue = checkBuffer(tessere, buffer, bonus, grid, k, visited))){
            if(bonusValue > (*maxBonus)){
                (*maxBonus) = bonusValue;
                for (int i = 0; i < k; i++) {
                    bestSol[i] = tessere[i];
                }
            }
        }

        for (int i = 0; i < grid.NR; i++) {
            for (int j = 0; j < grid.NC; j++) {
                visited[i][j] = 0;
            }
        }

        return;
    }

    for (int i = 0; i < grid.NR; i++) {
        for (int j = 0; j < grid.NC; j++) {
            tessere[pos].r = i;
            tessere[pos].c = j;
            strcpy(tessere[pos].token.val, grid.token[i][j].val);
            powerset(pos+1, k, tessere, buffer, grid, bonus, maxBonus, bestSol, visited);
            tessere[pos].r = 0;
            tessere[pos].c = 0;
        }
    }
}

void ottimizzazione(Grid grid, Bonus bonus){
    int pos = 0;
    int k = 3;
    int maxBonus = 0;
    Token *buffer;
    Tessera *tessere;
    Tessera *bestSol;

    int **visited = calloc(grid.NR, sizeof (int *));
    for (int i = 0; i < grid.NR; i++) {
        visited[i] = calloc(grid.NC, sizeof (int));
    }

    tessere = malloc(sizeof(Tessera) * k);
    buffer = malloc(sizeof (Token) * k);
    bestSol = malloc(sizeof(Tessera) * k);
    powerset(pos, k, tessere, buffer, grid, bonus, &maxBonus, bestSol, visited);

    printf("\nLa scelta ottima ha portato a: %d", maxBonus);
}