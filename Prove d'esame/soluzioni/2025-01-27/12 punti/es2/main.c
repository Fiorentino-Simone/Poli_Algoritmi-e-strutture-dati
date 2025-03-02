#include <stdio.h>

#define N 5

typedef struct node *link;

struct node{
    char item[N];
    link l, r;
};

typedef struct binarySearch {
    link root;
    link z;
} BST;

int BSTprintMax2(BST b);

int main() {
    BST b;
    int lunghezza;

    return 0;
}



int BSTprintMax2(BST b) {
    char pathLeaf[N];
    int maxl = findMaxlR(b.root,b.z,&pathLeaf);
    printf("maxl: %d\n", maxl);
    printf("path nodes\n");
    printPathToLeafR(b.root, KEYget(&pathLeaf));
}
