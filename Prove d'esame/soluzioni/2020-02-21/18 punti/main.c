#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "BST.h"

// PROTOTIPI
void generazione_menu(int P, int N_piatti, Portate *elencoPiatti);

int main() {
    int P = 0, N_piatti = 0;
    FILE *fin;
    Portate *elencoPiatti;

    printf("Inserisci il valore di P (menu di P piatti): ");
    scanf("%d", &P);

    fin = fopen("piatti.txt", "r");
    if(!fin){
        printf("Errore nell'apertura del file!");
        exit(-1);
    }
    fscanf(fin, "%d\n", &N_piatti);
    elencoPiatti = calloc(N_piatti, sizeof(Portate));
    for (int i = 0; i < N_piatti; i++) {
        fscanf(fin, "%s %s %s %f\n", elencoPiatti[i].nome, elencoPiatti[i].portata, elencoPiatti[i].tipologia, &elencoPiatti[i].costo);
    }
    fclose(fin);

    // generazione di tutti i menu disponibili
    generazione_menu(P, N_piatti, elencoPiatti);

    free(elencoPiatti);
    return 0;
}

/* FUNCTIONS */
static void comb_sempl(FILE *fout, int pos, int start, int n, int *sol, int N_piatti, Portate *elencoPiatti, BST menus){
    float costo_totale = 0.0;
    Menu menu;
    if(pos >= n){
        fprintf(fout, "\n");
        menu.elencoPortate = calloc(n, sizeof(Portate));
        for (int i = 0; i < n; i++) {
            strcpy(menu.elencoPortate[i].nome, elencoPiatti[sol[i]].nome);
            strcpy(menu.elencoPortate[i].portata, elencoPiatti[sol[i]].portata);
            strcpy(menu.elencoPortate[i].tipologia, elencoPiatti[sol[i]].tipologia);
            menu.elencoPortate[i].costo = elencoPiatti[sol[i]].costo;
            costo_totale += elencoPiatti[sol[i]].costo;
            fprintf(fout, "%s %s %s %f\n", menu.elencoPortate[i].nome, menu.elencoPortate[i].portata, menu.elencoPortate[i].tipologia, menu.elencoPortate[i].costo);
        }
        fprintf(fout, "Il costo totale del menu vale: %.2f", costo_totale);
        fprintf(fout, "\n");
        menu.costoTotale = costo_totale;
        BSTinsertLeaf(menus, menu, n);
        return;
    }

    for (int i = start; i < N_piatti; i++) {
        sol[pos] = i;
        comb_sempl(fout, pos+1, i+1, n, sol, N_piatti, elencoPiatti, menus);
    }
}

void generazione_menu(int P, int N_piatti, Portate *elencoPiatti){
    int start = 0;
    int pos = 0;
    BST menus = BSTinit();

    int *sol = calloc(P, sizeof(int));
    Portate *elencoPiattiBis = calloc(N_piatti*2, sizeof (Portate));

    for (int i = 0, j = 0; i < N_piatti*2; i+=2, j++) {
        elencoPiattiBis[i] = elencoPiattiBis[i+1] = elencoPiatti[j];
    }

    FILE *fout;
    fout = fopen("Piatti_res.txt", "w");
    comb_sempl(fout, pos, start, P, sol, 2*N_piatti, elencoPiattiBis, menus);

    BSTprint(menus, P);

    fclose(fout);
    free(sol);
    BSTfree(menus);
}