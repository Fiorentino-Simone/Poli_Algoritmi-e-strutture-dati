#include <stdio.h>
#include <stdlib.h>
#include "dipendenti.h"

struct dipendenti_t{
    Dipendente *dipendenti;
    int nDip;
};

Dipendenti DIPENDENTIinit(int nDip){
    Dipendenti dip = malloc(sizeof(*dip));
    dip->dipendenti = malloc(nDip * sizeof(Dipendente));
    dip->nDip = nDip;
    return dip;
}

Dipendenti DIPENDENTIread(FILE *fin){
    Dipendenti dip;
    int nDip;
    fscanf(fin, "%d", &nDip);
    dip = DIPENDENTIinit(nDip);
    for (int i = 0; i < nDip; i++) {
        dip->dipendenti[i] = DIPENDENTEacquisizione(fin);
    }
    return dip;
}

void DIPENDENTIprint(Dipendenti dip){
    for (int i = 0; i < dip->nDip; i++) {
        DIPENDENTEprint(dip->dipendenti[i]);
    }
}