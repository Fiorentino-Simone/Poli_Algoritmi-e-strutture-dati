#ifndef INC_18_PUNTI_DIPENDENTE_H
#define INC_18_PUNTI_DIPENDENTE_H

#define MAXL 20

typedef struct {
    int matr;
    char nome[MAXL], cognome[MAXL];
    int operaio, amministrativo, tecnico, informatico;
} Dipendente;

Dipendente DIPENDENTEacquisizione(FILE *fin);
void DIPENDENTEprint(Dipendente d);

#endif //INC_18_PUNTI_DIPENDENTE_H
