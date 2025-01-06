#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

// DEFINE
#define MAXL 30

// TYPEDEF
typedef enum
{
    r_leggiFile,
    r_individuaArchiCardMin,
    r_creaDAG,
    r_camminoMassimo,
    r_fine,
    r_err
} comando_e;

// PROTOTIPI
comando_e leggi_comando();

int main()
{
    // DICHIARAZIONI
    int continua, dagCreated;
    comando_e comando;
    Graph G;
    char filename[MAXL];
    FILE *fin;
    Edge *backEdges;

    continua = 1;
    dagCreated = 0;
    fin = NULL;
    G = NULL;

    while (continua)
    {
        comando = leggi_comando();
        switch (comando)
        {
            case r_leggiFile:
                printf("Inserisci il nome del file: ");
                scanf("%s", filename);
                fin = fopen(filename, "r");
                if (fin == NULL)
                {
                    printf("Errore nell'apertura del file!");
                    exit(1);
                }
                G = GRAPHload(fin);
                GRAPHstore(G, stdout);
                fclose(fin);
                break;
            case r_individuaArchiCardMin:
                if (G == NULL)
                {
                    printf("Devi prima caricare il grafo!");
                    break;
                }
                backEdges = malloc(GRAPHcount(G) * sizeof(Edge));
                for (int i = 0; i < GRAPHcount(G); i++)
                {
                    GRAPHfindBackEdges(G, i, backEdges);
                }
                break;
            case r_creaDAG:
                if (G == NULL)
                {
                    printf("Devi prima caricare il grafo!");
                    break;
                }
                DAGcreate(G, backEdges);
                dagCreated = 1;
                break;
            case r_camminoMassimo:
                if (dagCreated == 0)
                {
                    printf("Devi prima creare il DAG!");
                    break;
                }
                DAGpathMax(G);
                break;
            case r_fine:
                continua = 0;
                break;
            default:
                printf("Comando errato!");
                break;
        }
        printf("\n");
    }

    GRAPHfree(G);
    return 0;
}

// FUNCTIONS
comando_e leggi_comando()
{
    comando_e c;
    char cmd[MAXL];
    char tabella[r_err][MAXL] = {
        "leggi_file",
        "individua_archi_card_min",
        "crea_dag",
        "cammino_massimo",
        "fine"};

    printf("Inserisci uno tra questi comandi \n(leggi_file, \n individua_archi_card_min, \n crea_dag, \n cammino_massimo, \n fine): ");
    scanf("%s", cmd);
    strlwr(cmd);
    printf("\n");

    c = r_leggiFile;
    while (c < r_err && strcmp(tabella[c], cmd) != 0)
    {
        c++;
    }
    return c;
}