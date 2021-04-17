#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct _Card {
    int number;
    struct _Card *next;
} Card;

Card *top;

Card *add(int step, int num) {
    Card *newCard = (Card *)malloc(sizeof(Card));
    newCard->number = num;
    if (step == 0) {
        newCard->next = top;
        top = newCard;
    } else {
        Card *cur = top;
        while (--step)   // cur = 'target index - 1'
            cur = cur->next;
        newCard->next = cur->next;
        cur->next = newCard;
    }
    return top;
}

// step = start index, bias = num of chosen cards
Card *cut(int step, int bias) {
    Card *front = top, *tail = top;
    while (--step) {   // front = 'target index - 1'
        front = front->next;
        tail = tail->next;
    } while (bias--)   // tail = the last chosen card
        tail = tail->next;

    Card *newTop = front->next;   // the first chosen card should be new top
    front->next = tail->next ? tail->next : NULL;
    tail->next = top;
    return newTop;
}

void traversal(Card *top) {
    while (top) {
        printf("%d\n", top->number);
        top = top->next;
    }
}

int main() {
    int num_card, num_ope, input;
    scanf("%d%d", &num_card, &num_ope);

    top = (Card *)malloc(sizeof(Card));
    Card *cur = top;
    for (int i = 1; i <= num_card; i++) {
        scanf("%d", &input);
        cur->number = input;
        if (i != num_card) {
            cur->next = (Card *)malloc(sizeof(Card));
            cur = cur->next;
        } else
            cur->next = NULL;
    }

    char operation[5];
    int idx, num, a, b;
    for (int i = 0; i < num_ope; i++) {
        scanf("%s", operation);
        if (strcmp(operation, "ADD") == 0) {
            scanf("%d%d", &idx, &num);
            top = add(idx, num);
        } else {
            scanf("%d%d", &a, &b);
            if (a) top = cut(a, b);
        }
    }
    traversal(top);
    return 0;
}