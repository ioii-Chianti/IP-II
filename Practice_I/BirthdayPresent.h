#ifndef FUNCTION_H
#define FUNCTION_H
#include <stdlib.h>

/* 當K會變: 開一個陣列存所有K */

typedef struct _Node {
    struct _Node *prev;
    struct _Node *next;
    int val;
    int tag;
} Node;

int n, k, q, num_nodes;
Node *head, *median, *tail, *tanoshi;

Node *newNode(int val) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = val;
    node->tag = 0;   // init tag to -1 when k is moved
    node->prev = node->next = NULL;
    return node;
}

void push(int x) {
    num_nodes++;
    if (head == NULL) {
        head = newNode(x);
        tail = head;
        median = head;
        tanoshi = head;
    } else {
        tail->next = newNode(x);
        tail->next->prev = tail;
        tail = tail->next;
    } 
    if (num_nodes > 1 && num_nodes % 2)   // 增加成奇數的時候中位會動
        median = median->next;
    // PrintList();
}
void pop() {
    Node *node = median;   // 奇偶數影響中位
    median = num_nodes % 2 ? median->prev : median->next;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    free(node);
    num_nodes--;
    // PrintList();
}

void programming_tanoshi() {
    head->tag = 1;
    while (tanoshi->next) {
        tanoshi->next->tag = 1;
        tanoshi = tanoshi->next;
    }
}

void KuoYangTeTe() {
    Node *node = head;
    while (node->tag) {
        if (node->val > k || node->val != 1 || node->val != 0)
            node->val %= k;
        node = node->next;
    }
}

#endif
