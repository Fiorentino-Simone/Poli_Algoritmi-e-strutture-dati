#include <stdio.h>
#include <stdlib.h>

#define MAXL 50
#define MAX_ELEM 20
#define MAX_DIAGS 3
#define BONUS_MULTIPLIER 1.5
#define DIFFICULTY_THRESHOLD 8

// TYPEDEF
typedef struct
{
    char nome[MAXL];
    int tipologia;  // 0 = acrobatic, 1 = transition
    int entrata;    // 0 = back, 1 = front
    int uscita;     // 0 = back, 1 = front
    int precedenza; // 0 = normal, 1 = required
    int finale;     // 0 = no, 1 = yes
    float valore;
    int difficolta;
} Element;

typedef struct
{
    float score;
    int hasBonus;
    float maxScore;
} Diagonal;

// PROTOTIPI
void file_read(char *filename, Element *elements, int *elemCount);

int checkSol(int **sol, Element *elementi);
void calcolateValue(int **sol, Element *elementi, Diagonal *diagonali);

void bestSol(Element *elementi, int n, int dd, int dp);
void bestSolR(int pos, int diag, int **sol, int **bestSolM, float *tot, Element *elementi, int n, int ddVal, int dpVal, int dd, int dp, Diagonal *diagonals);

void printSolution(Diagonal *diagonals, int **bestSolM, Element *elementi, int dd, int dp, float tot);

int main()
{
    // DICHIARAZIONI
    char filename[MAXL];
    int dd, dp;
    Element elements[MAX_ELEM];
    int elemCount = 0;

    printf("Inserire il nome del file: ");
    scanf("%s", filename);
    printf("Inserire il valore di DD: ");
    scanf("%d", &dd);
    printf("Inserire il valore di DP: ");
    scanf("%d", &dp);

    file_read(filename, elements, &elemCount);

    bestSol(elements, elemCount, dd, dp);

    return 0;
}

// FUNCTIONS
void file_read(char *filename, Element *elements, int *elemCount)
{
    FILE *file;

    file = fopen(filename, "r");
    if (!file)
    {
        printf("Errore nell'apertura del file: %s\n", filename);
        exit(1);
    }

    fscanf(file, "%d", elemCount);

    for (int i = 0; i < *(elemCount); i++)
    {
        fscanf(file, "%s %d %d %d %d %d %f %d",
                elements[i].nome,
                &elements[i].tipologia,
                &elements[i].entrata,
                &elements[i].uscita,
                &elements[i].precedenza,
                &elements[i].finale,
                &elements[i].valore,
                &elements[i].difficolta);
    }
    fclose(file);
}

void bestSol(Element *elementi, int n, int dd, int dp)
{
    int **sol, **bestSolM;
    float tot;
    Diagonal *diagonals;

    sol = malloc(sizeof(int *) * MAX_DIAGS);
    bestSolM = malloc(sizeof(int *) * MAX_DIAGS);
    tot = 0;
    diagonals = malloc((sizeof(Diagonal) * MAX_DIAGS));

    for (int i = 0; i < MAX_DIAGS; i++)
    {
        sol[i] = malloc(sizeof(int) * MAX_ELEM);
        bestSolM[i] = malloc(sizeof(int) * MAX_ELEM);
        for (int j = 0; j < MAX_ELEM; j++)
        {
            sol[i][j] = -1;
        }

        diagonals[i].score = 0;
        diagonals[i].hasBonus = 0;
    }

    bestSolR(0, 0, sol, bestSolM, &tot, elementi, n, 0, 0, dd, dp, diagonals);

    printSolution(diagonals, bestSolM, elementi, dd, dp, tot);

    for (int i = 0; i < MAX_DIAGS; i++)
    {
        free(sol[i]);
        free(bestSolM[i]);
    }
    free(sol);
    free(bestSolM);
    free(diagonals);
}

static int checkValidity(int pos, int i, Element *elementi, int **sol, int diag, int ddVal, int dpVal, int dd, int dp)
{
    if (pos == 0)
    {
        if (elementi[i].entrata == 0 || elementi[i].precedenza == 1)
        {
            return 0;
        }
    }
    else if (pos > 0)
    {
        if (elementi[i].entrata != elementi[sol[diag][pos - 1]].uscita)
        {
            return 0;
        }
    }
    if (ddVal + elementi[i].difficolta > dd || dpVal + elementi[i].difficolta > dp)
    {
        return 0;
    }
    return 1;
}

void bestSolR(int pos, int diag, int **sol, int **bestSolM, float *tot, Element *elementi, int n, int ddVal, int dpVal, int dd, int dp, Diagonal *diagonali)
{
    float value;
    if (diag >= MAX_DIAGS)
    {
        if (checkSol(sol, elementi))
        {
            calcolateValue(sol, elementi, diagonali);
            value = diagonali[0].score + diagonali[1].score + diagonali[2].score;
            if (value > *tot)
            {
                *tot = value;
                diagonali[0].maxScore = diagonali[0].score;
                diagonali[1].maxScore = diagonali[1].score;
                diagonali[2].maxScore = diagonali[2].score;
                for (int i = 0; i < MAX_DIAGS; i++)
                {
                    for (int j = 0; j < MAX_ELEM; j++)
                    {
                        bestSolM[i][j] = sol[i][j];
                    }
                }
            }
        }
        return;
    }

    for (int i = 0; i < n; i++)
    {
        if (checkValidity(pos, i, elementi, sol, diag, ddVal, dpVal, dd, dp))
        {
            sol[diag][pos] = i;
            bestSolR(pos + 1, diag, sol, bestSolM, tot, elementi, n, ddVal + elementi[i].difficolta, dpVal + elementi[i].difficolta, dd, dp, diagonali);
        }
    }

    if (pos > 0)
    {
        sol[diag][pos] = -1;
        bestSolR(0, diag + 1, sol, bestSolM, tot, elementi, n, 0, dpVal, dd, dp, diagonali);
    }
}

int checkSol(int **sol, Element *elementi)
{
    int acrob, avanti, indietro, seq;

    acrob = avanti = indietro = seq = 0;
    for (int i = 0; i < MAX_DIAGS; i++)
    {
        acrob = 0;
        for (int j = 0; j < MAX_ELEM && sol[i][j] != -1; j++)
        {
            if (elementi[sol[i][j]].tipologia != 0)
            {
                acrob = 1;
                if (j > 0 && elementi[sol[i][j - 1]].tipologia != 0)
                {
                    seq = 1;
                }
            }
            if (elementi[sol[i][j]].tipologia == 2)
            {
                avanti = 1;
            }
            if (elementi[sol[i][j]].tipologia == 1)
            {
                indietro = 1;
            }
        }
        if (!acrob)
        {
            return 0;
        }
    }
    if (!avanti || !indietro || !seq)
        return 0;
    else
        return 1;
}

void calcolateValue(int **sol, Element *elementi, Diagonal *diagonali)
{
    float diag[MAX_DIAGS];
    float coeff;

    coeff = 1.0;
    diag[0] = diag[1] = diag[2] = 0.0;
    for (int i = 0; i < MAX_DIAGS; i++)
    {
        for (int j = 0; j < MAX_ELEM && sol[i][j] != -1; j++)
        {
            diag[i] += elementi[sol[i][j]].valore;
            if (i == 2)
            {
                if (elementi[sol[i][j]].difficolta >= DIFFICULTY_THRESHOLD)
                {
                    coeff = BONUS_MULTIPLIER;
                }
            }
        }
    }
    diagonali[0].score = diag[0];
    diagonali[1].score = diag[1];
    diagonali[2].score = diag[2] * coeff;
    if (coeff == BONUS_MULTIPLIER)
    {
        diagonali[2].hasBonus = 1;
    }
}

void printSolution(Diagonal *diagonals, int **bestSolM, Element *elementi, int dd, int dp, float tot)
{
    printf("DD = %d DP = %d\n", dd, dp);
    printf("TOT = %.3f\n", tot);
    for (int i = 0; i < MAX_DIAGS; i++)
    {
        if (diagonals[i].hasBonus){
            printf("DIAG #%d > %.2f (BONUS)\n", i + 1, diagonals[i].maxScore);
        } else {
            printf("DIAG #%d > %.2f\n", i + 1, diagonals[i].maxScore);
        }
        for (int j = 0; j < MAX_ELEM && bestSolM[i][j] != -1; j++)
        {
            printf("%s ", elementi[bestSolM[i][j]].nome);
        }
        printf("\n");
    }
}