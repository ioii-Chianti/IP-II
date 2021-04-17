#include <stdio.h>
#include <stdlib.h>
#define MAX 10000

typedef struct _Node {
    int data;
    struct _Node *next;
    int edgeToNext;
} Node;

typedef struct {
    int numVertex;
    Node **adjList;
} Graph;

int numNodes;
Graph *graph;

Node *newNode(int value, int edge) {
    Node *node = (Node *)malloc(sizeof(Node));
    node->data = value;
    node->edgeToNext = edge;
    node->next = NULL;
    return node;
}

Graph *newGraph(int num) {
    Graph *g = (Graph *)malloc(sizeof(Graph));
    g->numVertex = num;
    g->adjList = (Node **)malloc(num * sizeof(Node *));
    for (int i = 0; i < num; i++)
        g->adjList[i] = NULL;
    return g;
}

void addEgde(int u, int v, int edge) {
    Node *node = newNode(v, edge);
    node->next = graph->adjList[u];
    graph->adjList[u] = node;

    node = newNode(u, edge);
    node->next = graph->adjList[v];
    graph->adjList[v] = node;
}

int main() {
    int n, Q;
    scanf("%d%d", &n, &Q);
    numNodes = n;
    graph = newGraph(numNodes);

    while (--n) {
        int u, v, x;
        scanf("%d%d%d", &u, &v, &x);
        addEdge(u, v, x);
    }

    int seq[MAX], numSeqElement, numOne, input;
    while (Q--) {
        scanf("%d%d", &numSeqElement, &numOne);
        for (int i = 0; i < numSeqElement; i++) {
            scanf("%d", &input);
            seq[i] = input;
        }
    }

    return 0;
}