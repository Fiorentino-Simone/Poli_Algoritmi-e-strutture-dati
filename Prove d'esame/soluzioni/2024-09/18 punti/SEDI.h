#ifndef INC_18_PUNTI_SEDI_H
#define INC_18_PUNTI_SEDI_H

typedef struct sediProntoSoccorso *SEDI;

int SEDIgetN(SEDI sol);
char *SEDIgetCitta(SEDI sol, int i);

int SEDIsearchCitta(SEDI sol, char *citta);

int checkIfServirla(SEDI sol, char *citta);

#endif //INC_18_PUNTI_SEDI_H
