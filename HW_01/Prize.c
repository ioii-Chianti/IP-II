#include <stdio.h>
#include <stdlib.h>
// #include "function.h"

typedef struct _Node{
    int number;
    struct _Node* prev;
    struct _Node* next;
} Node;

int People;
Node* head;

Node *newNode(Node *previous, int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    previous->next = node;
    node->number = value;
    node->prev = previous;
    node->next = NULL;
    return node;
}

Node *createList(int n) {
    People = n;
    head = (Node *)malloc(sizeof(Node));
    head->number = 1, head->prev = head->next = NULL;
    Node *node = head;
    for (int i = 2; i <= n; i++)
        node = node->next = newNode(node, i);
    node->next = head;
    head->prev = node;
    return head;
}

void solveJosephus(int n, int m) {
    int lucky, cnt, firstRound = 1;
    Node *cur = head, *pre = NULL, *nxt = NULL;
    for (int i = 0; i < m; i++) {
        scanf("%d", &lucky);
        cnt = lucky % People ? lucky % People : People;   // minimize counting

        if (!firstRound)
            cur = lucky % 2 ? nxt : pre;
        else firstRound = 0;

        while (--cnt)
            cur = lucky % 2 ? cur->next : cur->prev;
        printf("%d\n", cur->number);
        pre = cur->prev, nxt = cur->next;   // remember the previous and next of current node
        pre->next = nxt, nxt->prev = pre;   // remove current node
        People--;
    }
}

int main() {
    int n, k;
    while (scanf("%d%d", &n, &k) != EOF) {
        head = createList(n);
        solveJosephus(n, k);
    }
    return 0;
}
