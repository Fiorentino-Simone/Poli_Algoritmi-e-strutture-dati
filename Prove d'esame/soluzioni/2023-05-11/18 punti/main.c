#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main() {
    Graph G;

    // 1) Scansione
    G = GRAPHload();

    // 2) Problema di verifica
    if(GRAPHverifica(G, "proposta.txt") == 1){
        printf("Soluzione proposta valida!");
    } else {
        printf("Soluzione proposta non valida");
    }

    // 3) Problema di ricerca
    GRAPHsolve(G);

    return 0;
}
