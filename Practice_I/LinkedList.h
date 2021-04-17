#ifndef NODE
#define NODE
#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>

typedef struct node {
	struct node *next;
	struct node *prev;
	unsigned short val;
} Node;

int length;
Node *tail;
void do_I(Node **head, size_t pos, unsigned short val);
void do_E(Node **head, size_t begin_pos, size_t end_pos);
void do_P(Node *head, size_t pos);
void do_R(Node **head, unsigned short val);
void do_S(Node *head);

Node *newNode(unsigned short val) {
	Node *node = (Node *)malloc(sizeof(Node));
	node->val = val;
	node->prev = node->next = NULL;
	return node;
}

void do_I(Node **head, size_t pos, unsigned short val) {
	if (pos >= length) {
		if (*head == NULL) {
			*head = newNode(val);
			tail = *head;
		} else {
			tail->next = newNode(val);
			tail->next->prev = tail;   //new
			tail = tail->next;
		}
	} else {
		Node *node = newNode(val);
		if (pos == 0) {
			node->next = *head;
			(*head)->prev = node;
			*head = node;
		} else {
			Node *cur = *head;
			while (--pos)
				cur = cur->next;
			node->prev = cur;	
			node->next = cur->next;
			cur->next->prev = node;
			cur->next = node;
		}
	}
	length++;
	do_S(*head);
}

void do_E(Node **head, size_t begin_pos, size_t end_pos) {
	// 兩個相等或兩個都超過: 不會變
	if (begin_pos == end_pos || begin_pos > length) {
		do_S(*head);
		return;
	}
	// 從頭開始、結束超過範圍: 全部不見
	if (begin_pos == 0 && end_pos > length) {
		(*head)->next = NULL;
		tail = NULL;
		free(head);
		length = 0;
		// do_S(*head);
		return;
	}
	// 從頭開始、中間結束
	if (begin_pos == 0 && end_pos <= length) {
		length -= end_pos;
		Node *rear = *head;
		while (end_pos--)
			rear = rear->next;
		rear->prev = NULL;
		(*head) = rear;
	}
	// 從內開始、在內結束
	else if (begin_pos > 0 && end_pos <= length) {
		int bias = end_pos - begin_pos;
		length -= bias;
		Node *front = *head, *rear = NULL;
		while (begin_pos--)
			front = front->next;
		rear = front;
		while (bias--)
			rear = rear->next;
		front->prev->next = rear;
		rear->prev = front->prev;
	}
	// 只刪最後一個
	else if (begin_pos == length && end_pos > length) {
		length--;
		tail = tail->prev;
		tail->next = NULL;
	}
	// 中間開始、結束超過
	else if (begin_pos < length && end_pos > length) {
		length -= (length - begin_pos);
		Node *node = (*head);
		while (begin_pos--)
			node = node->next;
		tail = node->prev;
		node->prev->next = NULL;
	}
	// do_S(*head);
}

void do_P(Node *head, size_t pos) {
	if (head) {
		if (pos >= length)
			printf("%d ", tail->val);
		else {
			Node *node = head;
			while (pos--)
				node = node->next;
			printf("%d ", node->val);
		}
	}
}
void do_R(Node **head, unsigned short val) {
	Node *node = *head;
	while (node) {
		if (node->val == val) {
			if (node->prev == NULL && node->next == NULL) {
				*head = NULL;
				tail = NULL;
			} else if (node->prev == NULL && node->next) {
				node = node->next;
				node->prev = NULL;
			} else if (node->prev && node->next) {
				node->prev->next = node->next;
				node->next->prev = node->prev;
			} else if (node->prev && node->next == NULL) {
				tail = node->prev;
				node = node->prev;
				node->next = NULL;
			}
			length--;
		}
		node = node->next;
	}
}

void do_S(Node *head) {
	Node *node = head;
	// printf("LEN: %d ; TAIL: %d\n", length, tail ? tail->val : -1);
	while (node) {
		printf("%d ", node->val);
		node = node->next;
	}
}

#endif