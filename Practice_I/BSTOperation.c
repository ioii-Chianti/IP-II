#include <stdio.h>
#include <stdlib.h>
#define MAXLV 99999

typedef struct _BTNode {
    int data;
    struct _BTNode *left;
    struct _BTNode *right;
} BTNode;

// 種樹的時候一邊記下每層的資訊即可省時
int height, sums[MAXLV], nodes[MAXLV];  // sum and # node of each level
BTNode *Root;

BTNode *newNode(int val) {
    BTNode *node = (BTNode *)malloc(sizeof(BTNode));
    node->data = val;
    node->left = node->right = NULL;
    return node;
}

// 遞迴建樹比較詳細，遍歷的方式建樹每次要從root開始！
void insertNode(BTNode **root, int value, int level) {
    if (*root == NULL) {    // 找到位置後newNode並更新該LEVEL的資訊
        *root = newNode(value);
        if (height < level)
            height = level;
        sums[level] += value;   // 加上該LV的總和
        nodes[level]++;         // 加上該LV的NODE數量
    } else {    // 遞迴找空位置，每遞迴一次LEVEL就會加深
        if (value < (*root)->data)
            return insertNode(&((*root)->left), value, level + 1);
        else if ((*root)->data < value)
            return insertNode(&((*root)->right), value, level + 1);
    }
}

void inOrder(BTNode *root) {
    if (root) {
        BTNode *node = root;
        inOrder(node->left);
        printf("%d ", root->data);
        inOrder(node->right);
    }
}

void freeTree(BTNode *root) {
    if (root) {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}

int main() {
    int N, Q, input;
    scanf("%d", &N);
    while (N--) {
        scanf("%d", &input);
        insertNode(&Root, input, 1);
    }   // build tree
        
    scanf("%d", &Q);
    char operation[10];
    while (Q--) {
        scanf("%s", operation);
        if (operation[0] == 'G')
            printf("%d\n", height);
        else if (operation[0] == 'S') {
            scanf("%d", &input);
            if (input > height || input < 1)
                printf("0\n");
            else
                printf("%d\n", sums[input]);
        } else if (operation[0] == 'A') {
            scanf("%d", &input);
            if (input > height || input < 1)
                printf("0\n");
            else
                printf("%.3f\n", (float)sums[input] / nodes[input]);
        } else {
            if (Root) {
                inOrder(Root);
                printf("\n");
            } else printf("NULL\n");
        }
    }
    freeTree(Root);
    return 0;
}