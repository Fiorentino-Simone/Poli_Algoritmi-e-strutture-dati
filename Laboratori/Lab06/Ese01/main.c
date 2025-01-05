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
void displaySol(int *P, int i, Att *v);
int compare(const void *a, const void *b);

int main()
{
    // DICHIARAZIONI
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
    *v = (Att *)malloc((*n + 1) * sizeof(Att)); // +1 per la sentinella

    for (int i = 1; i <= (*n); i++)
    {
        fscanf(fin, "%d %d", &((*v)[i].s), &((*v)[i].f));
    }

    // Sentinella
    (*v)[0].s = 0;
    (*v)[0].f = 0;

    fclose(fin);
}

int compare(const void *a, const void *b)
{
    Att *att1 = (Att *)a;
    Att *att2 = (Att *)b;
    return att1->f - att2->f;
}

void attSel(int n, Att *v)
{
    int *dp = (int *)calloc(n + 1, sizeof(int));
    int *P = (int *)calloc(n + 1, sizeof(int));
    int maxDur = 0, last = 0;

    // Ordina le attività per tempo di fine
    qsort(v, n + 1, sizeof(Att), compare);

    for (int i = 0; i <= n; i++)
    {
        dp[i] = 0;
        P[i] = -1;
    }

    for (int i = 1; i <= n; i++)
    {
        dp[i] = v[i].f - v[i].s; // Durata corrente
        P[i] = 0;

        // Controllo del predecessore
        for (int j = 0; j < i; j++)
        {
            if ((v[j].f <= v[i].s) && (dp[i] < dp[j] + (v[i].f - v[i].s)))
            {
                dp[i] = dp[j] + (v[i].f - v[i].s);
                P[i] = j;
            }
        }

        if (dp[i] > maxDur)
        {
            maxDur = dp[i];
            last = i;
        }
    }

    printf("Migliore durata: %d\n", maxDur);
    printf("Attivita' selezionate:\n");
    displaySol(P, last, v);

    free(dp);
    free(P);
}

void displaySol(int *P, int i, Att *v)
{
    if (i == 0)
        return;

    displaySol(P, P[i], v);

    printf("Attivita': inizio=%d, fine=%d\n", v[i].s, v[i].f);
}
