#include <stdio.h>
#include "Item.h"

typedef struct node *link;
struct node
{
    Item item;
    link left;
    link right;
};

int count(link root)
{
    if (root == NULL)
        return 0;
    return count(root->left) + count(root->right) + 1;
}

int height(link root)
{
    int u, v;
    if (root == NULL)
        return -1;
    u = height(root->left);
    v = height(root->right);
    if (u > v)
        return u + 1;
    return v + 1;
}

void preOrder(link root){
    if(root == NULL){
        return;
    }
    printf("%s ", root->name);
    preOrder(root->left);
    preOrder(root->right);
}

void inOrder(link root){
    if(root == NULL){
        return;
    }
    inOrder(root->left);
    printf("%s ", root->name);
    inOrder(root->right);
}

void postOrder(link root){
    if(root == NULL){
        return;
    }
    postOrder(root->left);
    postOrder(root->right);
    printf("%s ", root->name);
}