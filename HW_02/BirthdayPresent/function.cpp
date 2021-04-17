#include <bits/stdc++.h>
#include <iostream>
// #include "function.h"
using namespace std;

int numNode;
Node *tanoshi;

Node* newNode(int val) {
    Node *node = new Node;
    node->val = val;
    node->tag = 0;
    node->prev = node->next = NULL;
    return node;
}

KuoYangPresent::KuoYangPresent(int k) {
	this->head = this->mid = this->tail = NULL;
    this->k = k;
}

void KuoYangPresent::Push(int x) {
    numNode++;
    if (this->head == NULL) {
        this->head = newNode(x);
        this->tail = this->head;
        this->mid = this->head;
        tanoshi = this->head;
    } else {
        this->tail->next = newNode(x);
        this->tail->next->prev = this->tail;
        this->tail = this->tail->next;
    } 
    if (numNode > 1 && numNode % 2)   // 增加成奇數的時候中位會動
        this->mid = this->mid->next;
}

void KuoYangPresent::Pop() {
    Node *node = this->mid;   // 奇偶數影響中位
    this->mid = numNode % 2 ? this->mid->prev : this->mid->next;
    node->prev->next = node->next;
    node->next->prev = node->prev;
    delete node;
    numNode--;
}

void KuoYangPresent::ProgrammingTanoshi() {
    this->head->tag = 1;
    while (tanoshi->next) {
        tanoshi->next->tag = 1;
        tanoshi = tanoshi->next;
    }
}

void KuoYangPresent::KuoYangTeTe() {
    Node *node = this->head;
    while (node->tag) {
        if (node->val > this->k || node->val != 1 || node->val != 0)
            node->val %= this->k;
        node = node->next;
    }
}

void KuoYangPresent::PrintList() {
    Node *res = this->head;
    while (res) {
		printf("%d ", res->val);
		res = res->next;
	}
	puts("");
}