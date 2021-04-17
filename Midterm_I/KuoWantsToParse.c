#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <ctype.h>   // for isdigit()

typedef struct _Node {
    int value;
    char operator;
    struct _Node *left;
    struct _Node *right;
} BTNode;

char expr[120];
int pos;
BTNode *head;

BTNode* Factor();
BTNode* Expr();

BTNode* newNode(int value, char ch) {
    BTNode *node;
    node = (BTNode *) malloc(sizeof(BTNode));
    if (ch == 'N') {
        node->value = value;
        node->operator = 'N';
    } else {
        node->value = -1;
        node->operator = ch;
    }
    node->left = node->right = NULL;
    return node;
}

int findValue() {
    int buffer[100000] = {0}, bu = 1;
    buffer[0] = expr[pos + 1] - '0';
    while (isdigit(expr[pos]) && pos >= 0)
        buffer[bu++] = expr[pos--] - '0';

    int ret = 0;
    for (int i = bu - 1; i >= 0; i--)
        ret += (buffer[i] * pow(10, i));
    return ret;
}

void preOrder(BTNode* root) {
    if (root) {
        if (root->value == -1)
            printf("%c ", root->operator);
        else
            printf("%d ", root->value);
        preOrder(root->left);
        preOrder(root->right);
    }
}

BTNode* Factor() {
    char ch;
    BTNode *node = NULL;
    if (pos >= 0) {
        ch = expr[pos--];
        if (isdigit(ch))
            node = newNode(findValue(), 'N');
        else if (ch == ')') {
            node = Expr();
            if (expr[pos--] != '(')
                printf("Error!\n");
        }
    }
    return node;
}

BTNode* Expr() {
    char ch;
    BTNode *node = NULL, *right = NULL;
    if (pos >= 0) {
        right = Factor();

        if (pos > 0) {
            ch = expr[pos];
            if (ch == '+' || ch == '-') {
                node = newNode(-1, ch);
                node->right = right;
                pos--;
                node->left = Expr();
            } else
                node = right;
        } else
            node = right;
    }
    return node;
}

int main() {
    while((scanf("%s" , expr)) != EOF) {
        pos = strlen(expr) - 1;
        head = Expr();
        preOrder(head);
        printf("\n");
        head = NULL; 
    }
    
    return 0;
}