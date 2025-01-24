#include <stdio.h>
#include "dipendenti.h"
#include "divisioni.h"

typedef struct{
    int **compTot, **addTot;
    Abbinamento *abbinamenti;
    int nDiv, nMans, nDip;
} Associazioni;

Associazioni ASSOCIAZIONIread(FILE *fin, Dipendenti dip, Divisioni div);
Associazioni ASSOCIAZIONIcreate(int nDiv, int nMans, int nDip);

int main() {
    FILE *fin;
    Dipendenti dipendenti;
    Divisioni divisioni;
    Associazioni associazioni;

    // lettura dei dipendenti
    fin = fopen("dipendenti.txt", "r");
    dipendenti = DIPENDENTIread(fin);
    DIPENDENTIprint(dipendenti);

    // lettura delle divisioni
    fin = fopen("divisioni.txt", "r");
    divisioni = DIVISIONIread(fin);
    DIVISIONIprint(divisioni);

    // lettura delle associazioni
    fin = fopen("associazioni.txt", "r");
    associazioni = ASSOCIAZIONIcreate(fin, dipendenti, divisioni);


    fclose(fin);
    return 0;
}

// PROTOTIPO
Associazioni ASSOCIAZIONIread(FILE *fin, Dipendenti dip, Divisioni div){
    int nDiv, nDip, matricola, mansione, divisione, dipendente;
    Associazioni a;
    Dipendente d;
    char sigla[10], tipo;

    nDiv = DIVISIONIsize(div);
    fscanf(fin, "%d", &nDip);
    a = ASSOCIAZIONIcreate(nDiv, N, nDip);
    for(int i=0; i< nDip; i++){
        fscanf(fin, "%d %c %s", &matricola, &tipo, sigla);
        divisione = DIVISIONIsearch(div, sigla);
        dipendente = DIPENDENTIsearch(dip, matricola);
        a.abbinamenti[dipendente] = ABBINAMENTOcreate(divisione, mansione);
        (a.addTot[divisione][mansione])++;
        d=DIPENDENTIgetDipendente(dip, dipendente);
        a.compTot[divisione][mansione]=a.compTot[divisione][mansione]+d.competenze[mansione];
    }
    return a;
}

static int **malloc2D(int nr, int nc, int value){
    int **mat;
    int i, j;
    mat=(int**)malloc(nr*sizeof(int*));
    for(i=0; i<nr; i++){
        mat[i]=(int*)malloc(nc*sizeof(int));
    }

    for(i=0; i<nr; i++)
        for(j=0; j<nc; j++)
            mat[i][j]=value;
    return mat;
}

Associazioni ASSOCIAZIONIcreate(int nDiv, int nMans, int nDip){
    Associazioni a;
    a.nDiv = nDiv;
    a.nMans = nMans;
    a.nDip = nDip;
    a.compTot = malloc2D(nDiv, nMans, 0);
    a.addTot = malloc2D(nDiv, nMans, 0);
    a.abbinamenti = (Abbinamento*) malloc(nDip*sizeof(Abbinamento));
    return a;
}