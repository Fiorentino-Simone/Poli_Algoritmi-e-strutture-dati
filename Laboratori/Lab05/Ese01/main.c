#include <stdio.h>
#include <stdlib.h>

// TYPEDEF
typedef struct
{
    int s, f;
} Att;

// PROTOTIPI
void read_file(int *n, Att **v);

void attSel(int n, Att *v);
void powerset(int pos, Att *v, int n, int *sol, int *bestSol, int *bestDur, int currDur);
int check(Att *v, int *sol, int n);

int main()
{
    // DICHIARAZIONE
    int n;
    Att *v;

    read_file(&n, &v);

    attSel(n, v);

    free(v);
    return 0;
}

// FUNCTIONS
void read_file(int *n, Att **v)
{
    FILE *fin;

    fin = fopen("att.txt", "r");
    if (fin == NULL)
    {
        printf("Impossibile aprire il file!");
        exit(1);
    }

    fscanf(fin, "%d", n);
    *v = (Att *)malloc((*n) * sizeof(Att));

    for (int i = 0; i < (*n); i++)
    {
        fscanf(fin, "%d %d", &((*v)[i].s), &((*v)[i].f));
    }

    fclose(fin);
}

void attSel(int n, Att *v)
{
    int *sol = (int *)calloc(n, sizeof(int));
    int *bestSol = (int *)calloc(n, sizeof(int));
    int bestDur = 0;

    powerset(0, v, n, sol, bestSol, &bestDur, 0);

    printf("Migliore durata: %d\n", bestDur);
    printf("Attivita' selezionate:\n");
    for (int i = 0; i < n; i++)
    {
        if (bestSol[i] == 1)
        {
            printf("Attivita' %d: inizio=%d, fine=%d\n", i, v[i].s, v[i].f);
        }
    }

    free(sol);
    free(bestSol);
}

void powerset(int pos, Att *v, int n, int *sol, int *bestSol, int *bestDur, int currDur)
{
    if (pos >= n)
    {
        if (check(v, sol, n) == 1)
        {
            if (currDur > *(bestDur))
            {
                *bestDur = currDur;
                for (int i = 0; i < n; i++)
                {
                    bestSol[i] = sol[i];
                }
            }
        }
        return;
    }

    sol[pos] = 0;
    powerset(pos + 1, v, n, sol, bestSol, bestDur, currDur);
    sol[pos] = 1;
    powerset(pos + 1, v, n, sol, bestSol, bestDur, currDur + (v[pos].f - v[pos].s));
}

int check(Att *v, int *sol, int n)
{
    for (int i = 0; i < n; i++)
    {
        if (sol[i] == 1)
        {
            for (int j = i + 1; j < n; j++)
            {
                if (sol[j] == 1)
                {
                    // Verifica sovrapposizione
                    if ((v[i].s < v[j].f) && (v[j].s < v[i].f))
                    {
                        return 0;
                    }
                }
            }
        }
    }
    return 1;
}
