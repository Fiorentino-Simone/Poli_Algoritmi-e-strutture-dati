#include <stdio.h>
#include <stdlib.h>

// TYPEDEF
typedef struct
{
    int u, v;
} Arco;

/* PROTOTIPI */
void read_file(char *filename, int *N, int *E, Arco **archi);

void powerset(int pos, int i, Arco *val, int *sol, int *vertici, int n, int e);
int checkVertexCover(int *sol, int i, Arco *val, int e);

int main()
{
    // DICHIARAZIONI
    int N, E; // N --> NODI, E --> ARCHI
    int *sol, *vertici;
    Arco *archi;

    archi = NULL;

    read_file("grafo.txt", &N, &E, &archi);

    sol = (int *)malloc(N * sizeof(int));
    vertici = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < N; ++i)
    {
        vertici[i] = i;
    }

    printf("I possibili vertex cover sono: ");
    powerset(0, 0, archi, sol, vertici, N, E);

    free(archi);
    free(sol);
    free(vertici);
    return 0;
}

/* FUNCTIONS */
void read_file(char *filename, int *N, int *E, Arco **archi)
{
    FILE *fin;

    fin = fopen(filename, "r");
    if (fin == NULL)
    {
        printf("Errore nella lettura del file!");
        exit(1);
    }

    fscanf(fin, "%d %d", N, E);
    *archi = (Arco *)malloc((*E) * sizeof(Arco));

    for (int i = 0; i < (*E); i++)
    {
        fscanf(fin, "%d %d", &((*archi)[i].u), &((*archi)[i].v));
    }

    fclose(fin);
}

void powerset(int pos, int i, Arco *val, int *sol, int *vertici, int n, int e)
{
    if (pos >= n) // Condizione di terminazione
    {
        if (checkVertexCover(sol, i, val, e) == 1)
        {
            printf("(");
            for (int j = 0; j < i; j++)
            {
                printf("%d ", sol[j]);
            }
            printf(") ");
        }
        return;
    }

    // Prendo il vertice corrente
    sol[i] = vertici[pos];
    powerset(pos + 1, i + 1, val, sol, vertici, n, e);

    // Non prendo il vertice corrente
    powerset(pos + 1, i, val, sol, vertici, n, e);
}

int checkVertexCover(int *sol, int i, Arco *val, int e)
{
    int *trovato;

    trovato = (int *)calloc(e, sizeof(int));

    for (int j = 0; j < i; j++)
    {
        for (int k = 0; k < e; k++)
        {
            if (val[k].u == sol[j] || val[k].v == sol[j])
            {
                trovato[k] = 1;
            }
        }
    }

    for (int j = 0; j < e; j++)
    {
        if (trovato[j] == 0)
        {
            free(trovato);
            return 0;
        }
    }

    free(trovato);
    return 1;
}
