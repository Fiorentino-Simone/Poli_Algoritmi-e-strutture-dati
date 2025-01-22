#ifndef INC_18_PUNTI_DIPENDENTI_H
#define INC_18_PUNTI_DIPENDENTI_H

#include "dipendente.h"

typedef struct dipendenti_t *Dipendenti;

Dipendenti DIPENDENTIinit(int nDip);
Dipendenti DIPENDENTIread(FILE *fin);
void DIPENDENTIprint(Dipendenti dip);

#endif //INC_18_PUNTI_DIPENDENTI_H
