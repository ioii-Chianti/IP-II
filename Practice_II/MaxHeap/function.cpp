#include <iostream>
#include <string.h>
#include "function.h"
#define DEBUG 1
using namespace std;

/* class Array Max Heap */
void HeapifyArray (int *arr, int index, const string operation) {
    if (operation == "push") {
        // current node is root
        if (index == 1)
            return;
        // if: swap, else: already on right position
        if (arr[index] > arr[index / 2]) {
            int temp = arr[index];
            arr[index] = arr[index / 2];
            arr[index / 2] = temp;
            HeapifyArray(arr, index / 2, "push");
        } else
            return;
    } else if (operation == "pop") {
        // current node is leaf
        if (index * 2 == -1 && index * 2 + 1 == -1)
            return;
        
        // current node has at least one child
        // find the index of bigger child
        int bigChild = arr[index * 2] > arr[index * 2 + 1] ? index * 2 : index * 2 + 1;
        // if: swap, else: already on right position
        if (arr[index] < arr[bigChild]) {
            int temp = arr[index];
            arr[index] = arr[bigChild];
            arr[bigChild] = temp;
            HeapifyArray(arr, bigChild, "pop");
        } else
            return;
    }
}

// reusing base constructor to init Cnt = 0
Array_MAX_HEAP::Array_MAX_HEAP() : MAX_HEAP() { memset(array, -1, sizeof(array)); }

void Array_MAX_HEAP::PUSH(const int &item) {
    array[++Count] = item;
    HeapifyArray(array, Count, "push");
    if (DEBUG) printArray();
}

int Array_MAX_HEAP::MAX() const { return array[1]; }

int Array_MAX_HEAP::POP() {
    if (!Count) return -1;
    int ret = array[1];
    array[1] = array[Count];
    array[Count--] = -1;
    HeapifyArray(array, 1, "pop");

    if (DEBUG) printArray();
    return ret;
}


/* class List Max Heap */

void List_MAX_HEAP::preOrder(ListNode *root) {
    if (!root) return;
    cout << root->getValue() << " ";
    preOrder(root->getLeft());
    preOrder(root->getRight());
}

void List_MAX_HEAP::inOrder(ListNode *root) {
    if (!root) return;
    inOrder(root->getLeft());
    cout << root->getValue() << " ";
    inOrder(root->getRight());
}

List_MAX_HEAP::List_MAX_HEAP() : root(NULL) {}

void List_MAX_HEAP::PUSH(const int &value) {
    if (!Count)
        root = new ListNode(value);
    else {
        // find the parent of new node
        ListNode *toHeapify, *pivot = findparent(Count + 1, root);
        if (DEBUG) cout << "--- parent: " << pivot->value << endl;
        
        // decide left or right position to push node
        if (pivot->left == NULL) {
            pivot->left = new ListNode(value);
            pivot->left->parent = pivot;
            toHeapify = pivot->left;
        } else {
            pivot->right = new ListNode(value);
            pivot->right->parent = pivot;
            toHeapify = pivot->right;
        }

        // Heapify
        while (toHeapify != root) {
            if (toHeapify->value > toHeapify->parent->value) {
                int numA = toHeapify->value, numB = toHeapify->parent->value;
                toHeapify->value = numB;
                toHeapify->parent->value = numA;
                if (DEBUG) cout << "--- exchange: " << numA << " & " << numB << endl;
            }
            toHeapify = toHeapify->parent;
        }   // Heapify end
    }
    Count++;
    if (DEBUG) {
        cout << "--- preOrder: ";
        preOrder(root);
        cout << endl;
        cout << "--- inOrder: ";
        inOrder(root);
        cout << endl;
    }
}
int List_MAX_HEAP::MAX() const { return root ? root->value : -1; }
int List_MAX_HEAP::POP() {
    if (!Count) return -1;

    int ret = root->value;
    if (Count == 1)
        root = NULL;
    else {
        ListNode *toHeapify = root, *pivot = findparent(Count, root);
        // decide left or right position to pop node
        if (pivot->right) {
            root->value = pivot->right->value;
            pivot->right = NULL;
        } else {
            root->value = pivot->left->value;
            pivot->left = NULL;
        }

        // Heapify
        while (true) {
            // current node is leaf
            if (toHeapify->left == NULL && toHeapify->right == NULL)
                break;

            // current node has only left child
            if (toHeapify->right == NULL) {
                if (toHeapify->value < toHeapify->left->value) {   // 且現在跟左子要交換
                    int numA = toHeapify->value, numB = toHeapify->left->value;
                    toHeapify->value = numB;
                    toHeapify->left->value = numA;
                    if (DEBUG) cout << "--- exchange: " << numA << " & " << numB << endl;
                }
                break;   // 無論這次有無交換都不會有下一次判斷交換
            }

            // current node has two child
            if (toHeapify->left && toHeapify->right) {
                // find the bigger child
                ListNode *bigChild = toHeapify->left->value > toHeapify->right->value ? toHeapify->left : toHeapify->right;
                // if: swap, else: already on right position
                if (toHeapify->value < bigChild->value) {
                    int numA = toHeapify->value, numB = bigChild->value;
                    toHeapify->value = numB;
                    bigChild->value = numA;
                    toHeapify = bigChild;  // 繼續往下判斷
                    if (DEBUG) cout << "--- exchange: " << numA << " & " << numB << endl;
                } else
                    break;
            }
        }   // end heapify
    }
    Count--;
    if (DEBUG) {
        cout << "--- preOrder: ";
        preOrder(root);
        cout << endl;
        cout << "--- inOrder: ";
        inOrder(root);
        cout << endl;
    }
    return ret;
}
void List_MAX_HEAP::deleteTree(ListNode *root) {
    if (!root) return;
    deleteTree(root->left);
    deleteTree(root->right);
    delete root;
}