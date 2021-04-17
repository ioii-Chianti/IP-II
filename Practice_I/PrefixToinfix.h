#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>

typedef struct treeNode {
    char data;
    struct treeNode *left;
    struct treeNode *right;
} Node;

void constructTree(Node** head);
void printInfix(Node *root);
void freeTree(Node *root);

void printInfix(Node *root) {   // 一樣是LDR，只是R要加上括號
    if (root == NULL)
        return;
    printInfix(root->left);   // L
    printf("%c", root->data);   // D
    if (root->right) {
        if (root->right->data == '&' || root->right->data == '|') {
            printf("(");
            printInfix(root->right);
            printf(")");
        } else
            printInfix(root->right);
    }
}

#endif