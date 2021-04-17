#include <stdio.h>
#include <stdlib.h>

typedef struct _Node {
    char data;
    struct _Node *left;
    struct _Node *right;
} BTNode;

BTNode *newNode(char data) {
    BTNode *node = (BTNode *)malloc(sizeof(BTNode));
    node->data = data;
    node->left = node->right = NULL;
    return node;
}

// Build a tree by prefix: DLR
BTNode *newTree() {
    char input;
    scanf("%c", &input);

    if (input == '&' || input == '|') {    // 用DLR建出來
        BTNode *node = newNode(input);
        node->left = newTree(node->left);
        node->right = newTree(node->right);
        return node;
    } else {
        BTNode *node = newNode(input);    // 遇到運算元就直接建NODE
        return node;
    }
}

int ans(BTNode *root, int v) {
    if (root->data == '&')
        return ans(root->left, v) & ans(root->right, v);
    else if (root->data == '|')
        return ans(root->left, v) | ans(root->right, v);
    else
        return (v >> (3 - (root->data - 'A'))) & 1;
}

void inOrder(BTNode *root) {
    if (root == NULL)
        return;
    printf("(");
    inOrder(root->left);
    printf("%c", root->data);
    inOrder(root->right);
    printf(")");
    return;
}

int main() {
    BTNode *root = newTree();

    inOrder(root);
    printf("\n");

    // use binary to represent ABCD
    // ABCD
    // 0000 = 0
    // 0001 = 1
    // ...
    for (int i = 0; i < 16; i++) {
        printf("%d %d %d %d ", (i >> 3) & 1, (i >> 2) & 1, (i >> 1) & 1, i & 1);
        printf("%d\n", ans(root, i));
    }

    return 0;
}