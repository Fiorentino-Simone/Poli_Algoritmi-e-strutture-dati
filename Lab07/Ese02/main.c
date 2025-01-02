#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_ELEMS 100
#define MAX_NAME_LEN 100
#define MAX_DIAG 5

// Struttura per rappresentare un elemento
typedef struct {
    char name[MAX_NAME_LEN];
    int type; // 0: transizione, 1: acrobatico indietro, 2: acrobatico avanti
    int entry_dir; // 0: spalle, 1: fronte
    int exit_dir;  // 0: spalle, 1: fronte
    int precedence; // 0: primo elemento permesso, 1: non primo
    int finale; // 0: non finale, 1: finale
    float score;
    int difficulty;
} Element;

// Funzione per leggere il file degli elementi
int readElements(const char *filename, Element elements[], int *numElements) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Errore apertura file");
        return 0;
    }

    fscanf(file, "%d", numElements);
    for (int i = 0; i < *numElements; i++) {
        fscanf(file, "%s %d %d %d %d %d %f %d",
               elements[i].name,
               &elements[i].type,
               &elements[i].entry_dir,
               &elements[i].exit_dir,
               &elements[i].precedence,
               &elements[i].finale,
               &elements[i].score,
               &elements[i].difficulty);
    }

    fclose(file);
    return 1;
}

// Funzione per verificare se una sequenza di elementi forma una diagonale valida
int isValidDiagonal(Element diag[], int len, int maxDifficulty) {
    int hasAcrobatic = 0, totalDifficulty = 0;

    for (int i = 0; i < len; i++) {
        totalDifficulty += diag[i].difficulty;
        if (diag[i].type == 1 || diag[i].type == 2) {
            hasAcrobatic = 1;
        }
        if (i > 0 && diag[i - 1].exit_dir != diag[i].entry_dir) {
            return 0; // Direzioni incompatibili
        }
    }

    if (totalDifficulty > maxDifficulty || !hasAcrobatic) {
        return 0;
    }

    return 1;
}

// Funzione ricorsiva per generare tutte le diagonali valide
void generateDiagonals(Element elements[], int numElements, Element currentDiag[], int diagLen, int maxDifficulty, int maxElements, int index, float *bestScore, Element bestDiag[], int *bestLen) {
    if (diagLen > 0 && isValidDiagonal(currentDiag, diagLen, maxDifficulty)) {
        float score = 0;
        for (int i = 0; i < diagLen; i++) {
            score += currentDiag[i].score;
        }
        if (score > *bestScore) {
            *bestScore = score;
            *bestLen = diagLen;
            memcpy(bestDiag, currentDiag, diagLen * sizeof(Element));
        }
    }

    if (diagLen == maxElements) return;

    for (int i = index; i < numElements; i++) {
        currentDiag[diagLen] = elements[i];
        generateDiagonals(elements, numElements, currentDiag, diagLen + 1, maxDifficulty, maxElements, i + 1, bestScore, bestDiag, bestLen);
    }
}

// Funzione per calcolare il programma ottimale
void findBestProgram(Element elements[], int numElements, int maxDifficultyDiag, int maxDifficultyProg) {
    Element bestDiags[3][MAX_DIAG];
    int bestLens[3] = {0};
    float bestScores[3] = {0.0};
    float totalBestScore = 0.0;

    for (int i = 0; i < numElements; i++) {
        Element diag1[MAX_DIAG], diag2[MAX_DIAG], diag3[MAX_DIAG];
        int len1 = 0, len2 = 0, len3 = 0;
        float score1 = 0.0, score2 = 0.0, score3 = 0.0;

        generateDiagonals(elements, numElements, diag1, 0, maxDifficultyDiag, MAX_DIAG, 0, &score1, diag1, &len1);
        for (int j = 0; j < numElements; j++) {
            generateDiagonals(elements, numElements, diag2, 0, maxDifficultyDiag, MAX_DIAG, 0, &score2, diag2, &len2);
            for (int k = 0; k < numElements; k++) {
                generateDiagonals(elements, numElements, diag3, 0, maxDifficultyDiag, MAX_DIAG, 0, &score3, diag3, &len3);

                float totalScore = score1 + score2 + score3;
                if (len3 > 0 && diag3[len3 - 1].finale == 1 && diag3[len3 - 1].difficulty >= 8) {
                    score3 *= 1.5; // Applica bonus
                    totalScore = score1 + score2 + score3;
                }

                int totalDifficulty = 0;
                for (int l = 0; l < len1; l++) totalDifficulty += diag1[l].difficulty;
                for (int l = 0; l < len2; l++) totalDifficulty += diag2[l].difficulty;
                for (int l = 0; l < len3; l++) totalDifficulty += diag3[l].difficulty;

                if (totalDifficulty <= maxDifficultyProg && totalScore > totalBestScore) {
                    totalBestScore = totalScore;
                    bestLens[0] = len1;
                    bestLens[1] = len2;
                    bestLens[2] = len3;
                    memcpy(bestDiags[0], diag1, len1 * sizeof(Element));
                    memcpy(bestDiags[1], diag2, len2 * sizeof(Element));
                    memcpy(bestDiags[2], diag3, len3 * sizeof(Element));
                    bestScores[0] = score1;
                    bestScores[1] = score2;
                    bestScores[2] = score3;
                }
            }
        }
    }

    printf("Miglior programma trovato:\n");
    for (int i = 0; i < 3; i++) {
        printf("Diagonale #%d (%.2f):\n", i + 1, bestScores[i]);
        for (int j = 0; j < bestLens[i]; j++) {
            printf("%s ", bestDiags[i][j].name);
        }
        printf("\n");
    }
    printf("Punteggio totale: %.2f\n", totalBestScore);
}

int main() {
    Element elements[MAX_ELEMS];
    int numElements;

    if (!readElements("elementi.txt", elements, &numElements)) {
        return 1;
    }

    int DD = 10; // Difficoltà massima per diagonale
    int DP = 20; // Difficoltà massima per programma

    findBestProgram(elements, numElements, DD, DP);

    return 0;
}
