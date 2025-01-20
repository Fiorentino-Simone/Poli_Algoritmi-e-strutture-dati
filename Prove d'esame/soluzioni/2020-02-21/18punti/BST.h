#ifndef INC_18PUNTI_BST_H
#define INC_18PUNTI_BST_H

#define MAXL 100

// TYPEDEF
typedef struct {
    char nome[MAXL];
    char portata[MAXL];
    char tipologia[MAXL];
    float costo;
} Portate;

typedef struct{
    Portate *elencoPortate;
    float costoTotale;
} Menu;

typedef struct tree *BST;

BST BSTinit();
void BSTfree(BST bst);

void BSTinsertLeaf(BST bst, Menu menu, int P);
void BSTprint(BST bst, int P);

#endif //INC_18PUNTI_BST_H
