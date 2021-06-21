#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#define DEBUG 1
using namespace std;

vector<int> diamond_towns;
vector<int> neighbors[10005];
int shortest_distance[100005];
bool visited[100005] = {false};

struct Node {
    int id;
    int shortest;
    Node(int id, int l = -1) : id(id), shortest(l) {}
    Node(){};
};

int main() {
    int num_towns, num_roads, num_diamonds;
    cin >> num_towns >> num_roads >> num_diamonds;
    while (num_roads--) {
        int x, y;
        cin >> x >> y;
        neighbors[x].push_back(y);
        neighbors[y].push_back(x);
    }
    while (num_diamonds--) {
        int x;
        cin >> x;
        diamond_towns.push_back(x);
    }
    // int 版的 memset incl<algo>
    fill(shortest_distance, shortest_distance + 100005, -1);

    queue<Node> bfs;
    bfs.push(Node(-1));   // virtual root

    while (!bfs.empty()) {
        Node cur = bfs.front();
        bfs.pop();

        cur.shortest++;
        if (DEBUG) { cout << "Root: " << cur.id << " / " << cur.shortest <<  endl; }

        if (cur.shortest == 0) {
            for (int id : diamond_towns) {
                bfs.push(Node(id, 0));
                shortest_distance[id] = 0;
                visited[id] = true;
                if (DEBUG) { cout << "lv0: " << id << endl; }
            }
        } else {
            for (auto id : neighbors[cur.id]) {
                if (!visited[id]) {
                    bfs.push(Node(id, cur.shortest));
                    shortest_distance[id] = cur.shortest;
                    visited[id] = true;
                    if (DEBUG) { cout << "lv" << cur.shortest << ": " << id << endl; }
                }
            }
        }
        bool done = true;
        for (int i = 1; i <= num_towns; i++)
            if (!visited[i]) {
                done = false;
                break;
            }
        if (done) {
            if (DEBUG) cout << "done\n";
            break;
        }
    }

    for (int i = 1; i <= num_towns; i++)
        cout << shortest_distance[i] << endl;

    return 0;
}