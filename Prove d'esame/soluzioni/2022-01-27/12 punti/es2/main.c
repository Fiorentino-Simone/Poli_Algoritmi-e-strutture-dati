#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node *link;

struct node{
    int item;
    link l;
    link r;
};

typedef struct binaryTree{
    link root;
} BT;

static link NEW_node(int item){
    link node = malloc(sizeof(*node));
    node->item = item;
    node->r = node->l = NULL;
    return node;
}

// PROPOSTA 1: se il valore del nodo corrente è più piccolo del minimo o maggiore del massimo allora errore!!
static int check(link node, int min, int max){
    // se l'albero è vuoto
    if(node == NULL){
        return 1;
    }

    // se il valore del nodo corrente è più piccolo del minimo o maggiore del massimo allora errore!!
    if(node->item < min || node->item > max){
        return 0;
    }

    return check(node->l, min, node->item-1) &&
           check(node->r, node->item+1, max);
}

static int f(BT bt){
    return check(bt.root, INT_MIN, INT_MAX);
}

//PROPOSTA 2: controllo la visita in order che l'elemento i-esimo sia sempre minore di quello successivo
static int count(link node){
    if(node == NULL){
        return 0;
    }
    return count(node->l) + count(node->r) + 1;
}

static void visitaInOrder(link node, int *inOrder, int *k){
    if(node == NULL){
        return;
    }

    visitaInOrder(node->l, inOrder, k);
    inOrder[(*k)++] = node->item;
    visitaInOrder(node->r, inOrder, k);
}

void wrapperInOrder(BT bt){
    int k = 0;
    int numeroNodi = count(bt.root);
    int *inOrder = malloc(sizeof(int) * numeroNodi);
    visitaInOrder(bt.root, inOrder, &k);
    for (int i = 0; i < k-1; i++) {
        if(inOrder[i] > inOrder[i+1]){
            printf("l'albero binario NON risulta un BST");
            return;
        }
    }
    printf("l'albero binario risulta un BST");
}

int main() {
    BT bt;

    bt.root = NEW_node(19);
    bt.root->l = NEW_node(5);
    bt.root->r = NEW_node(25);
    bt.root->l->l = NEW_node(2);
    bt.root->l->r = NEW_node(7);
    bt.root->r->l = NEW_node(20);
    bt.root->r->r = NEW_node(30);

    if(f(bt)){
        printf("l'albero binario risulta un BST");
    }
    else {
        printf("l'albero binario NON risulta un BST");
    }
    printf("\n");

    // altro modo con la visita in order
    wrapperInOrder(bt);
    printf("\n");
    return 0;
}
