#include <stdio.h>
#include <stdlib.h>
#include "divisione.h"

struct divisione_t {
    char sigla[MAXL];
    Statistiche statistiche[N];

    // Associazioni
    Associazione *associazioni;
    int dimA, maxDimA;
};

Divisione DIVISIONEinit(){
    Divisione div = malloc(sizeof(*div));
    return div;
}

void DIVISIONEfree(Divisione d){
    free(d);
}

Divisione DIVISIONEacquisizione(FILE *fin){
    Divisione d = DIVISIONEinit();
    fscanf(fin, "%s", d->sigla);
    for (int i = 0; i < N; ++i) {
        fscanf(fin, "%d %d %d", &d->statistiche[i].m, &d->statistiche[i].cmin, &d->statistiche[i].r);
    }
    return d;
}

void DIVISIONEprint(Divisione d){
    printf("%s\n", d->sigla);
    for (int i = 0; i < N; i++) {
        printf("%d %d %d\n", d->statistiche[i].m, d->statistiche[i].cmin, d->statistiche[i].r);
    }
}

char *DIVISIONEgetSigla(Divisione d){
    return d->sigla;
}