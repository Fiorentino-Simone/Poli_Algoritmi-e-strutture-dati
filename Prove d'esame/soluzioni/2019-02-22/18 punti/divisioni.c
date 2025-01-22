
#include "divisioni.h"

struct divisioni_t{
    Divisione *divisioni;
    int nDiv;
};

Divisioni DIVISIONIinit(int nDiv){
    Divisioni div = malloc(sizeof(*div));
    div->divisioni = malloc(nDiv * sizeof(Divisione));
    div->nDiv = nDiv;
    return div;
}

Divisioni DIVISIONIread(FILE *fin){
    Divisioni div;
    int nDiv;
    fscanf(fin, "%d", &nDiv);
    div = DIVISIONIinit(nDiv);
    for (int i = 0; i < nDiv; i++) {
        div->divisioni[i] = DIVISIONEacquisizione(fin);
    }
    return div;
}

void DIVISIONIprint(Divisioni div){
    for (int i = 0; i < div->nDiv; i++) {
        DIVISIONEprint(div->divisioni[i]);
    }
}