#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

// DEFINE
#define MAXL 50

// TYPEDEF
typedef enum
{
    r_leggiFile,
    r_stampaOrdinata,
    r_verificaAdiacenza,
    r_generaListaDaMatrice,
    r_fine,
    r_err
} comando_e;

// PROTOTIPI
comando_e leggi_comando();

int main() {
    // DICHIARAZIONI
    int continua, sceltaRappr;
    comando_e comando;
    Graph G;
    char filename[MAXL];
    FILE *fin;

    continua = 1;
    sceltaRappr = 0;
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
                if (fin == NULL){
                    printf("Errore nell'apertura del file!");
                    exit(1);
                }
                G = GRAPHload(fin);
                printf("Vuoi inserire anche la rappresentazione con la lista delle adiacenze? (1 = si, 0 = no): ");
                scanf("%d", &sceltaRappr);
                if (sceltaRappr == 1){
                    G = GRAPHloadL(G, fin);
                }
                GRAPHstore(G, stdout);
                fclose(fin);
                break;
            case r_stampaOrdinata:
                if (G == NULL){
                    printf("Devi prima leggere il file!");
                    break;
                }
                GRAPHstoreOrd(G, stdout);
                break;
            case r_verificaAdiacenza:
                if (G == NULL){
                    printf("Devi prima leggere il file!");
                    break;
                }
                printf("Vuoi usare la rappresentazione con la matrice delle adiacenze o con la lista delle adiacenze? (0 = matrice, 1 = lista): ");
                scanf("%d", &sceltaRappr);
                GRAPHverificaAdiacenza(G, sceltaRappr);
                break;
            case r_generaListaDaMatrice:
                if (G == NULL){
                    printf("Devi prima leggere il file!");
                    break;
                }
                G = GRAPHloadLFromM(G, fin);
                GRAPHstore(G, stdout);
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
        "stampa_ordinata",
        "verifica_adiacenza",
        "genera_lista_da_matrice",
        "fine"
    };

    printf("Inserisci uno tra questi comandi \n(leggi_file, \n stampa_ordinata, \n verifica_adiacenza, \n genera_lista_da_matrice, \n fine): ");
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