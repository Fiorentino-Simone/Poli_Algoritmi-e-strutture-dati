#include <stdio.h>
#include "dipendenti.h"
#include "divisioni.h"

int main() {
    FILE *fin;
    Dipendenti dipendenti;
    Divisioni divisioni;

    // lettura dei dipendenti
    fin = fopen("dipendenti.txt", "r");
    dipendenti = DIPENDENTIread(fin);
    DIPENDENTIprint(dipendenti);

    // lettura delle divisioni
    fin = fopen("divisioni.txt", "r");
    divisioni = DIVISIONIread(fin);
    DIVISIONIprint(divisioni);
    return 0;
}
