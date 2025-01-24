#include <stdio.h>

#include "LIST.h"

int main() {

    LIST list;

    list = LISTinit();

    LISTpopolate(list);

    printf("Stampa della lista prima di f: ");
    LISTprint(list);

    f(list);

    printf("Stampa della lista dopo di f: ");
    LISTprint(list);

    LISTfree(list);
    return 0;
}
