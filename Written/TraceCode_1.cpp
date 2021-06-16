#include <iostream>
# define DUMMY_VALUE 8787
using namespace std;


typedef struct Node {
    int value;
    struct Node *prv, *nxt;
} Node;
// memory allocation of Node structure
Node* new_node(int val) {
    Node *ptr = (Node*)malloc(sizeof(Node));
    ptr->value = val;
    ptr->prv = ptr->nxt = NULL;
    return ptr;
}
// declaration of pointer to head and rear
Node *head = NULL, *rear = NULL;

// implementation 1:
void impl_1(int *arr, int n) {
    head = new_node(arr[0]), rear = head;
    for(int i = 1; i < n; i++) {
        Node *ptr = new_node(arr[i]);
        rear->nxt = ptr, ptr->prv = rear;
        rear = ptr;
    }
}
// implementation 2:
void impl_2(int *arr, int n) {
    head = new_node(DUMMY_VALUE), rear = head;
    head->nxt = rear, rear->prv = head;
    for(int i = 0; i < n; i++) {
        Node *ptr = new_node(arr[i]);
        ptr->nxt = rear, ptr->prv = rear->prv;
        rear->prv->nxt = ptr;
        rear->prv = ptr;
    }
}
// implementation 3:
void impl_3(int *arr, int n) {
    head = new_node(DUMMY_VALUE), rear = new_node(DUMMY_VALUE);
    head->nxt = rear, rear->prv = head;
    for(int i = 0; i < n; i++) {
        Node *ptr = new_node(arr[i]);
        ptr->nxt = rear, ptr->prv = rear->prv;
        rear->prv->nxt = ptr;
        rear->prv = ptr;
    }
}

void print_list(Node *begin, Node *end) {
    for(Node *ptr = begin; ptr != end; ptr = ptr->nxt)
        printf("%d ", ptr->value);
    printf("\n");
}

int main() {
    int arr[5] = {1, 2, 3, 4, 5};
    // use either one of the implementations
    impl_1(arr, 5);
    print_list(head, NULL);
    impl_2(arr, 5);
    print_list(head->nxt, rear);
    impl_3(arr, 5);
    print_list(head->nxt, rear);
}