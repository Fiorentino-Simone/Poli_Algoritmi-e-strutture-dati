#include <stdio.h>
#include "list.h"

int main()
{
    list l1 = LISTcreate();
    LISTload(l1);

    list l2 = LISTcreate();
    LISTload(l2);

    splice(l1, l2, 1, 2);
    printf("Stampa della lista 1: ");
    LISTshow(l1);
    printf("\n");
    printf("Stampa della lista 2: ");
    LISTshow(l2);

    LISTfree(l1);
    LISTfree(l2);
    return 0;
}
