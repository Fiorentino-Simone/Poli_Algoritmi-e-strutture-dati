#include <stdlib.h>
#include <stdio.h>
#include "dipendente.h"

Dipendente DIPENDENTEacquisizione(FILE *fin){
    Dipendente d;
    fscanf(fin,"%d %s %s %d %d %d %d", &d.matr, d.nome, d.cognome, &d.operaio, &d.amministrativo, &d.tecnico, &d.informatico);
    return d;
}

void DIPENDENTEprint(Dipendente d){
    printf("\n");
    printf("%d %s %s %d %d %d %d", d.matr, d.nome, d.cognome, d.operaio, d.amministrativo, d.tecnico, d.informatico);
    printf("\n");
}