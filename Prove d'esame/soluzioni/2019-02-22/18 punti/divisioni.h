#ifndef INC_18_PUNTI_DIVISIONI_H
#define INC_18_PUNTI_DIVISIONI_H

#include <stdlib.h>
#include <stdio.h>

#include "divisione.h"

typedef struct divisioni_t *Divisioni;

Divisioni DIVISIONIinit(int nDiv);
Divisioni DIVISIONIread(FILE *fin);
void DIVISIONIprint(Divisioni div);

#endif //INC_18_PUNTI_DIVISIONI_H
