#include <stdio.h>
#include <stdlib.h>
// #include "function.h"

typedef struct _Node {
    int data;
    struct _Node *next;
} Node;

void deleteNode(Node ** nd, int data) {
    Node *previous = NULL, *current = *nd;
    data--;
    while (data--) {
        previous = current;
        current = current->next;
        if (current == NULL)
            return;
    }
    if (previous == NULL)
        *nd = (*nd)->next;
    else {
        previous->next = current->next;
        current = previous->next;
    }
}

Node *createList() {
    Node *head = (Node *)malloc(sizeof(Node));
    int input;
    scanf("%d", &input);
    if (input > -1) {
        head->data = input;
        head->next = createList();
    } else
        head = NULL;
    return head;
}

void printList(Node *head){
    Node *temp;
    for(temp = head; temp!=NULL; temp=temp->next) {
        printf("%d ", temp->data);
    }
}

void freeList(Node *head){
    Node *temp;
    for (temp = head; temp != NULL; temp = head) {
        head = head->next;
        free(temp);
    }
}

int main() {
    Node *head;
    int data;

    head = createList();

    while (1) {
        scanf("%d", &data);
        if (data > -1)
            deleteNode(&head, data);
        else
            break;
    }

    printList(head);
    freeList(head);
    return 0;
}
