#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ELEM 100
#define MAX_DIAGS 3
#define BONUS_MULTIPLIER 1.5

typedef struct {
    char name[50];
    int type;      // 0 = acrobatic, 1 = transition
    int entry;     // 0 = back, 1 = front
    int exit;      // 0 = back, 1 = front
    int precedence; // 0 = normal, 1 = required
    int isFinal;   // 0 = no, 1 = yes
    float value;
    int difficulty;
} Element;

typedef struct {
    int indices[MAX_ELEM];
    int count;
    int totalDifficulty;
    float score;
    int hasBonus;
} Diagonal;

// Funzioni utili
int isCompatible(Diagonal *diag, int pos, Element *elements, int idx, int maxDiagDifficulty);
void generateDiagonals(Diagonal *diagonals, int *diagCount, Element *elements, int elemCount, int maxDiagDifficulty);
void printSolution(Diagonal *diagonals, int diagCount, Element *elements, int dd, int dp);

// Funzione principale
int main() {
    char filename[100];
    int dd, dp;

    // Input da tastiera
    printf("Inserire il nome del file: ");
    scanf("%s", filename);
    printf("Inserire il valore di DD: ");
    scanf("%d", &dd);
    printf("Inserire il valore di DP: ");
    scanf("%d", &dp);

    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Errore nell'apertura del file: %s\n", filename);
        return 1;
    }

    int elemCount;
    fscanf(file, "%d", &elemCount);

    Element elements[MAX_ELEM];
    for (int i = 0; i < elemCount; i++) {
        fscanf(file, "%s %d %d %d %d %d %f %d",
               elements[i].name,
               &elements[i].type,
               &elements[i].entry,
               &elements[i].exit,
               &elements[i].precedence,
               &elements[i].isFinal,
               &elements[i].value,
               &elements[i].difficulty);
    }
    fclose(file);

    Diagonal diagonals[MAX_DIAGS];
    int diagCount = 0;

    generateDiagonals(diagonals, &diagCount, elements, elemCount, dd);
    printSolution(diagonals, diagCount, elements, dd, dp);

    return 0;
}

int isCompatible(Diagonal *diag, int pos, Element *elements, int idx, int maxDiagDifficulty) {
    if (diag->totalDifficulty + elements[idx].difficulty > maxDiagDifficulty) {
        return 0;
    }
    if (pos > 0) {
        int prevIdx = diag->indices[pos - 1];
        if (elements[prevIdx].exit != elements[idx].entry) {
            return 0;
        }
    }
    return 1;
}

void generateDiagonals(Diagonal *diagonals, int *diagCount, Element *elements, int elemCount, int maxDiagDifficulty) {
    for (int i = 0; i < elemCount; i++) {
        if (elements[i].precedence == 1) {
            Diagonal diag = { .count = 0, .totalDifficulty = 0, .score = 0, .hasBonus = 0 };
            diag.indices[diag.count++] = i;
            diag.totalDifficulty += elements[i].difficulty;
            diag.score += elements[i].value;

            for (int j = 0; j < elemCount; j++) {
                if (i != j && isCompatible(&diag, diag.count, elements, j, maxDiagDifficulty)) {
                    diag.indices[diag.count++] = j;
                    diag.totalDifficulty += elements[j].difficulty;
                    diag.score += elements[j].value;
                }
            }

            if (diag.totalDifficulty >= 8) {
                diag.score *= BONUS_MULTIPLIER;
                diag.hasBonus = 1;
            }

            diagonals[*diagCount] = diag;
            (*diagCount)++;
            if (*diagCount >= MAX_DIAGS) {
                break;
            }
        }
    }
}

void printSolution(Diagonal *diagonals, int diagCount, Element *elements, int dd, int dp) {
    printf("--- Test Case ---\n");
    printf("DD = %d DP = %d\n", dd, dp);

    float totalScore = 0;

    for (int i = 0; i < diagCount; i++) {
        Diagonal *diag = &diagonals[i];
        totalScore += diag->score;

        printf("DIAG #%d > %.3f", i + 1, diag->score);
        if (diag->hasBonus) {
            printf(" * %.1f (BONUS)", BONUS_MULTIPLIER);
        }
        printf("\n");

        for (int j = 0; j < diag->count; j++) {
            printf("%s ", elements[diag->indices[j]].name);
        }
        printf("\n");
    }

    totalScore += dp;
    totalScore *= dd / 10.0;

    printf("TOT = %.3f\n", totalScore);
}
