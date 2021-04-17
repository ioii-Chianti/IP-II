#include <stdio.h>
#include <stdlib.h>
// #include "function.h"

typedef struct _Tree_Node {
    int number;
    struct _Tree_Node* parent;
    struct _Tree_Node* left;
    struct _Tree_Node* right;
} Tree_Node;

Tree_Node *tree_head;

Tree_Node *newNode(int value) {
    Tree_Node *node = (Tree_Node *)malloc(sizeof(Tree_Node));
    node->number = value;
    node->parent = node->left = node->right = NULL;
    return node;
}

void add_node(int n) {
    if (tree_head == NULL)
        tree_head = newNode(n);
    else {
        Tree_Node *pre = NULL, *cur = tree_head;
        while (cur) {
            pre = cur;
            cur = n < cur->number ? cur->left : cur->right;
        }
        if (n < pre->number)
            pre->left = newNode(n);
        else
            pre->right = newNode(n);
    }
    
}

void showtree(Tree_Node *treenow) {
    if (treenow == NULL)
        return;
    Tree_Node *node = treenow;
    showtree(node->left);
    printf("%d ", treenow->number);
    showtree(node->right);
}

int main() {
    int n, a;
    scanf("%d", &n);
    while (n--) {
        scanf("%d", &a);
        add_node(a);
    } 
    showtree(tree_head);
}
