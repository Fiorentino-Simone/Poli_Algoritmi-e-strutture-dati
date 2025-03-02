#include <stdio.h>

#define K 3 // grado dell'albero

typedef struct nodo_t *link;

struct nodo_t{
    int item;
    float wt;
    link children[K];
};

typedef struct tree{
    link root;
} TREE;

int maxSum(link root, float *maxwt);

int main() {
    TREE t;
    float maxwt = 0;

    printf("Il nodo identificato è: %d, con peso: %2.f", maxSum(t.root, &maxwt), maxwt);

    return 0;
}

int maxSum(link root, float *maxwt){
    if(root == NULL){
        return -1;
    }

    float cnt = root->wt;
    for (int i = 0; i < K; i++) {
        if(root->children[i] != NULL){
            float weight;
            maxSum(root->children[i], &weight);
            cnt += weight;
        }
    }
    if(cnt > *maxwt){
        *maxwt = cnt;
        return root->item;
    }
    return -1;
}
