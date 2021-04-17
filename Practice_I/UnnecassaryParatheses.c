#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAXEXPR 260

/* Build a syntax tree by infix, print the tree by in order
   == infix to tree + prefix to infix */

typedef struct _BTNode {
    char data;
    struct _BTNode *left;
    struct _BTNode *right;
} BTNode;

BTNode *Root;
char expr[MAXEXPR];
int pos;
BTNode *Expression();
BTNode *Factor();

BTNode *newNode(char ch) {
    BTNode *node = (BTNode *)malloc(sizeof(BTNode));
    node->data = ch;
    node->left = node->right = NULL;
    return node;
}

BTNode *Expression() {
    char ch;
    BTNode *root = NULL, *right = NULL;
    if (pos >= 0) {
        right = Factor();
        if (pos > 0) {
            ch = expr[pos];
            if (ch == '|' || ch == '&') {
                root = newNode(ch);
                root->right = right;
                pos--;
                root->left = Expression();
            } else
                root = right;
        } else
            root = right;
    }
    return root;
}

BTNode *Factor() {
    char ch;
    BTNode *node = NULL;
    if (pos >= 0) {
        ch = expr[pos--];
        if ('A' <= ch && ch <= 'D')
            node = newNode(ch);          
        else if (ch == ')') {
            node = Expression();
            if (expr[pos--] != '(')
                printf("Error!\n");
        }
    }
    return node;
}

void inOrder(BTNode *root) {
    if (root) {
        inOrder(root->left);
        printf("%c", root->data);
        if (root->right) {
            if (root->right->data == '&' || root->right->data == '|') {
                printf("(");
                inOrder(root->right);
                printf(")");
            } else
                inOrder(root->right);
        }
    }
}

int main() {
    scanf("%s", expr);
    pos = strlen(expr) - 1;
    Root = Expression();
    inOrder(Root);
    return 0;
}