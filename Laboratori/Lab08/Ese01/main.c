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
int isValid(Element *e, int currentDifficulty, int dd, int dp, int entrance, int position, int *used, int index);
int compareElements(const void *a, const void *b);
void greedy_solution(Element *elements, int elemCount, int dd, int dp);

int main()
{
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
    greedy_solution(elements, elemCount, dd, dp);

    return 0;
}

void file_read(char *filename, Element *elements, int *elemCount)
{
    FILE *file = fopen(filename, "r");
    if (!file)
    {
        printf("Errore nell'apertura del file: %s\n", filename);
        exit(1);
    }

    fscanf(file, "%d", elemCount);
    for (int i = 0; i < *elemCount; i++)
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

int compareElements(const void *a, const void *b)
{
    Element *e1 = (Element *)a;
    Element *e2 = (Element *)b;

    if (e1->valore != e2->valore)
    {
        return (e2->valore > e1->valore) - (e2->valore < e1->valore);
    }
    return e2->difficolta - e1->difficolta;
}

int isValid(Element *e, int currentDifficulty, int dd, int dp, int entrance, int position, int *used, int index)
{
    if (used[index])
        return 0;
    if (position == 0 && e->precedenza == 1)
        return 0;
    if (currentDifficulty + e->difficolta > dd || currentDifficulty + e->difficolta > dp)
        return 0;
    if (position > 0 && entrance != e->entrata)
        return 0;
    return 1;
}

void greedy_solution(Element *elements, int elemCount, int dd, int dp)
{
    Diagonal diagonals[MAX_DIAGS] = {{0, 0, 0}, {0, 0, 0}, {0, 0, 0}};
    int solution[MAX_DIAGS][MAX_ELEM];
    int used[MAX_ELEM] = {0};
    float tot = 0.0;

    for (int i = 0; i < MAX_DIAGS; i++)
    {
        for (int j = 0; j < MAX_ELEM; j++)
        {
            solution[i][j] = -1;
        }
    }

    // Ordina gli elementi per valore decrescente
    qsort(elements, elemCount, sizeof(Element), compareElements);

    for (int diag = 0; diag < MAX_DIAGS; diag++)
    {
        int pos = 0;
        int ddVal = 0, dpVal = 0;

        for (int i = 0; i < elemCount; i++)
        {
            if (pos > 0)
            {
                int prevElement = solution[diag][pos - 1];
                if (!isValid(&elements[i], ddVal, dd, dp, elements[prevElement].uscita, pos, used, i))
                {
                    continue;
                }
            }
            else if (!isValid(&elements[i], ddVal, dd, dp, -1, pos, used, i))
            {
                continue;
            }

            solution[diag][pos++] = i;
            used[i] = 1; // mark l'elemento
            diagonals[diag].score += elements[i].valore;
            ddVal += elements[i].difficolta;
            dpVal += elements[i].difficolta;

            if (diag == 2 && elements[i].difficolta >= DIFFICULTY_THRESHOLD)
            {
                diagonals[diag].hasBonus = 1;
            }
        }

        if (diag == 2 && diagonals[diag].hasBonus)
        {
            diagonals[diag].score *= BONUS_MULTIPLIER;
        }
        diagonals[diag].maxScore = diagonals[diag].score;
        tot += diagonals[diag].score;
    }

    printf("DD = %d DP = %d\n", dd, dp);
    printf("TOT = %.3f\n", tot);
    for (int diag = 0; diag < MAX_DIAGS; diag++)
    {
        if (diagonals[diag].hasBonus)
        {
            printf("DIAG #%d > %.2f (BONUS)\n", diag + 1, diagonals[diag].maxScore);
        }
        else
        {
            printf("DIAG #%d > %.2f\n", diag + 1, diagonals[diag].maxScore);
        }
        for (int pos = 0; pos < MAX_ELEM && solution[diag][pos] != -1; pos++)
        {
            printf("%s ", elements[solution[diag][pos]].nome);
        }
        printf("\n");
    }
}
