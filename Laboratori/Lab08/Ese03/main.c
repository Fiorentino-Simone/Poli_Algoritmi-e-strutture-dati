#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "titoli.h"

// DEFINE
#define MAXL 50

// TYPEDEF
typedef enum
{
    r_leggiFile,
    r_ricercaTitolo,
    r_ricercaQuotazione,
    r_ricercaQuotazioneMinMaxFromRange,
    r_ricercaQuotazioneMinMaxFromAllPeriod,
    r_bilanciamentoAlberoQuotazioni,
    r_fine,
    r_err
} comando_e;

// PROTOTIPI
comando_e leggi_comando();

int main()
{
    // DICHIARAZIONI
    int continua;
    comando_e comando;
    LISTtitolo l;
    char filename[MAXL];
    FILE *fin;

    continua = 1;
    fin = NULL;
    l = LISTinit();
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
                l = readfile(fin, l);
                fclose(fin);
                break;
            case r_ricercaTitolo:
                if (fin)
                {
                    searchTitle(l);
                }
                else
                {
                    printf("Devi prima leggere il file!");
                }
                break;
            case r_ricercaQuotazione:
                if (fin)
                {
                    searchQuotation(l);
                }
                else
                {
                    printf("Devi prima leggere il file!");
                }
                break;
            case r_ricercaQuotazioneMinMaxFromRange:
                if (fin)
                {
                    searchQuotationMinMax(l);
                }
                else
                {
                    printf("Devi prima leggere il file!");
                }
                break;
            case r_ricercaQuotazioneMinMaxFromAllPeriod:
                if (fin)
                {
                    searchQuotationMinMaxAllPeriod(l);
                }
                else
                {
                    printf("Devi prima leggere il file!");
                }
                break;
            case r_bilanciamentoAlberoQuotazioni:
                if (fin)
                {
                    balanceTree(l);
                }
                else
                {
                    printf("Devi prima leggere il file!");
                }
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

    LISTfree(l);
    return 0;
}

// FUNCTIONS
comando_e leggi_comando()
{
    comando_e c;
    char cmd[MAXL];
    char tabella[r_err][MAXL] = {
        "leggi_file",
        "ricerca_titolo",
        "ricerca_quotazione",
        "ricerca_quotazione_minmax_from_range",
        "ricerca_quotazione_minmax_from_all_period",
        "bilanciamento_albero_quotazioni",
        "fine"
    };

    printf("Inserisci uno tra questi comandi \n(leggi_file, \n ricerca_titolo, \n ricerca_quotazione, \n ricerca_quotazione_minmax_from_range, \n ricerca_quotazione_minmax_from_all_period, \n bilanciamento_albero_quotazioni \n fine): ");
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