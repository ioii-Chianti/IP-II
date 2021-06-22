#include <queue>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// neighbors[i] is the neighbor towns of town i
vector<int> diamondTowns;
vector<int> neighbors[100005];
int Dist[100005];

struct Node {
    int id;
    int dist;
    Node(int id, int l) {
        this->id = id;
        this->dist = l;
    }
};

int main() {
    int N, M, K;
    cin >> N >> M >> K;
    for (int i = 0; i < M; i++) {
        int a, b;
        cin >> a >> b;
        neighbors[a].push_back(b);
        neighbors[b].push_back(a);
    }
    for (int i = 0; i < K; i++) {
        int x;
        cin >> x;
        diamondTowns.push_back(x);
    }
    fill(Dist, Dist + 100005, -1);

    queue<Node> Q;
    for (int id : diamondTowns) {
        Q.push(Node(id, 0));
        Dist[id] = 0;
    }
    while (!Q.empty()) {
        Node cur_node = Q.front();
        Q.pop();
        
        for (int id : neighbors[cur_node.id]) {
            if (Dist[id] == -1) {
                Q.push(Node(id, cur_node.dist + 1));
                Dist[id] = cur_node.dist + 1;
            }
        }
    }

    // Output
    for (int i = 1; i <= N; i++) {
        cout << Dist[i] << '\n';
    }
    return 0;
}