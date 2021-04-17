#include <stdio.h>
#include <stdlib.h>
#define MAX 5005

typedef struct _Node {
    int data;
    struct _Node *next;
} Node;

typedef struct {
    int numVertex;
    Node **adjList;
} Graph;

Graph *graph;
int degree[MAX];

Node *newNode(int value) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = value;
    node->next = NULL;
    return node;
}

// void removeNode(int toRemove, int neighbor) {
//     Node *pre = NULL, *cur = graph->adjList[neighbor];
//     if (cur) {
//         if (pre == NULL)
//             graph->adjList[neighbor] = cur->next;
//         else  {
//             while (cur->data != toRemove) {
//                 pre = cur;
//                 cur = cur->next;
//             }
//             pre->next = cur->next;
//         }
//     }
// }

Graph *newGraph(int num) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertex = num;
    graph->adjList = (Node **)malloc(num * sizeof(Node *));
    for (int i = 0; i < num; i++)
        graph->adjList[i] = NULL;
    return graph;
}

void addEdge(int x, int y) {
    // add edge from x to y
    Node *node = newNode(y);
    node->next = graph->adjList[x];
    graph->adjList[x] = node;
    // add edge from y to x
    node = newNode(x);
    node->next = graph->adjList[y];
    graph->adjList[y] = node;
    
    degree[x]++, degree[y]++;   // optional
}

void traversal() {
    for (int v = 0; v < graph->numVertex; v++) {
        Node *node = graph->adjList[v];
        printf("%d: ", v);
        while (node) {
            printf("%d, ", node->data);
            node = node->next;
        }
        printf("\n");
    }
}

void prufer(int n) {
    for (int i = 1; i <= n - 2; i++) {
        for (int j = 1; j <= n; j++) {
            if (degree[j] == 1) {
                int ans = graph->adjList[j]->data;
                degree[j]--, degree[ans]--;
                printf("%d ", ans);

                Node *pre = NULL, *cur = graph->adjList[ans];
                if (cur) {
                    if (cur->data == j)
                        graph->adjList[ans] = cur->next;
                    else {
                        while (cur->data != j) {
                            pre = cur;
                            cur = cur->next;
                        }
                        pre->next = cur->next;
                    }
                    break;
                }
            }
        }
    }
    printf("\n");
}

int main() {
    int n, x, y;
    scanf("%d", &n);
    graph = newGraph(n);
    while (--n) {
        scanf("%d%d", &x, &y);
        addEdge(x, y);
    }
    // traversal();
    prufer(graph->numVertex);

    return 0;
}