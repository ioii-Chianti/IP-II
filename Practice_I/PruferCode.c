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

Graph *newGraph(int num) {
    Graph *graph = (Graph *)malloc(sizeof(Graph));
    graph->numVertex = num;
    graph->adjList = (Node **)malloc(num * sizeof(Node *));
    for (int i = 0; i < num; i++)
        graph->adjList[i] = NULL;
    return graph;
}

void newEdge(int x, int y) {
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

void Prufer(int numv) {
    int rounds = numv - 2;
    while (rounds--)    // 只會刪掉N-2個node
        for (int i = 1; i <= numv; i++) {   // traverse all list
            if (degree[i] == 1) {
                int ans = graph->adjList[i]->data;   // 他鄰居就是答案
                degree[i]--, degree[ans]--;   // 鄰居也要記得--
                printf("%d ", ans); 
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
        newEdge(x, y);
    }
    // traversal();
    prufer(graph->numVertex);

    return 0;
}