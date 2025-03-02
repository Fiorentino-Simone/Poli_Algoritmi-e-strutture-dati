#include <stdio.h>
#define N 6

struct node {
    char *key;
    struct node *children[N];
};

typedef struct nTree{
    struct node *root;
} nTREE;

int countIf(nTREE tree);
int countNodes(struct node *root, int parentDegree);

int main() {
    // scritto solo come doveva fare
    nTREE tree;

    printf("Numero di nodi con più figli del padre: %d\n", countIf(tree));

    return 0;
}

int countIf(nTREE tree){
    if(tree.root == NULL) return 0;
    return countNodes(tree.root, -1) + 1; // la radice conta 1 di default
}

int countNodes(struct node *root, int parentDegree){
    if(root == NULL) return 0;

    //calcolo del grado dei figli
    int degree = 0;
    for (int i = 0; i < N; i++) {
        if(root->children[i] != NULL){
            degree++;
        }
    }

    int count = (parentDegree != -1 && degree > parentDegree) ? 1 : 0;
    for (int i = 0; i < N; i++) {
        count += countNodes(root->children[i], degree);
    }
    return count;
}