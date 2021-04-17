#ifndef FUNCTION_H
#define FUNCTION_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int operations[300009], operationIdx;

typedef struct _Node{
    struct _Node *prev;
    struct _Node *next;
    int val;
    int tag; // use this variable to store which operation will be performed on this element 
} Node;

Node *head, *median, *tail, *operateTag;
int numNodes;

void push(int x);
void pop();
void programming_tanoshi(int k);
void IP2_sugoi();
void KuoYangTeTe(); //You can either use this function or not depending on how you solve this problem

Node *newNode(int val) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->val = val;
    node->prev = node->next = NULL;
    node->tag = -1;
    return node;
}

void traversal() {
    printf("M: %d T: %d OP: %d\n", median->val, tail->val, operateTag->val);
    Node *node = head;
    while(node) {
        printf("%d ", node->val);
        node = node->next;
    }
    printf("\n");
}

void push(int x) {
    numNodes++;
    if (head == NULL) {
        head = newNode(x);
        median = head;
        tail = head;
        operateTag = head;
    } else {
        tail->next = newNode(x);
        tail->next->prev = tail;
        tail = tail->next;
    }
    if (numNodes > 1 && numNodes % 2) {
        median = median->next;
    }
    // traversal();
}
void pop() {
    Node *node = median;
    median = numNodes % 2 ? median->prev : median->next;
    if (node->prev && node->next) {
        node->prev->next = node->next;
        node->next->prev = node->prev;
    } else if (node->prev == NULL && node->next == NULL) {
        head = NULL;
    } else if (node->prev == NULL) {
        node = node->next;
        node->prev = NULL;
    } else if (node->next == NULL) {
        node = node->prev;
        node->next = NULL;
    }
    numNodes--;
    // traversal();
}
void programming_tanoshi(int k) {
    operations[operationIdx] = k;
    head->tag = 0;
    while (operateTag->next) {
        operateTag->next->tag = operationIdx;
        operateTag = operateTag->next;
    }
    // printf("01 op %d\n", operationIdx);
    operationIdx++;
}
void IP2_sugoi() {
    operations[operationIdx] = -1;
    head->tag = 0;
    while (operateTag->next) {
        operateTag->next->tag = operationIdx;
        operateTag = operateTag->next;
    }
    // printf("02 op %d\n", operationIdx);
    operationIdx++;
}
void KuoYangTeTe() {
    Node *node = head;
    while (node) {

        if (node->tag != -1) {
            if (node->val == 1 || node->val == 0) {
                node = node->next;
                continue;
            }
            for (int i = node->tag; i < operationIdx; i++) {
                if (node->val != 1 && node->val != 0) {
                    if (operations[i] == -1) {
                        node->val = floor(sqrt(node->val));
                    } else {
                        int divd = operations[i];
                        node->val = ceil((float)node->val / divd);
                    }
                }
            }
        }
        node = node->next;
    }
}

#endif