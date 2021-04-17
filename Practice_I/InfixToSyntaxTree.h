#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdlib.h>
#define MAXEXPR 256
#define NUMSYM 6

char expr[MAXEXPR];  // string to store the input expression.
int pos;             // current position of parsing, from end to start

typedef enum {ID_A, ID_B, ID_C, ID_D, OP_AND, OP_OR} TokenSet;
char sym[NUMSYM];

typedef struct _Node {
    TokenSet data;
    struct _Node *left, *right;
} BTNode;

BTNode *EXPR();
BTNode *FACTOR();
BTNode *makeNode(char c);
void freeTree(BTNode *root);
void printPrefix(BTNode *root);

BTNode *makeNode(char c) {
    BTNode *node = (BTNode *)malloc(sizeof(BTNode));
    for (int i = 0; i < NUMSYM; i++)
        if (c == sym[i])
            node->data = i;
    node->left = node->right = NULL;
    return node;
}

BTNode *FACTOR() {
    char ch;
    BTNode *node = NULL;
    if (pos >= 0) {   // 確認還沒處理完
        ch = expr[pos--];   // 給最後一個字元
        if (ch >= 'A' && ch <= 'D')
            node = makeNode(ch);    // 若是ID
        else if (ch == ')') {   // 若有括號
            node = EXPR();  // 遞迴處理裡面的運算
            if (expr[pos--] != '(') {   // 處理完應為左括號
                printf("Error!\n");       // 否則錯誤
                freeTree(node);
            }
        }
    }
    return node;
}

BTNode *EXPR() {
    char ch;
    BTNode *node = NULL, *right = NULL;
    if (pos >= 0) {
        right = FACTOR();
        
        if (pos > 0) {
            ch = expr[pos];
            if (ch == '|' || ch == '&') {
                node = makeNode(ch);
                node->right = right;
                pos--;
                node->left = EXPR();
            } else
                node = right;
        } else
            node = right;
    }
    return node;
}

#endif