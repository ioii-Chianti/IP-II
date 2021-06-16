#include <iostream>
#include <set>
using namespace std;

int main() {
    int T, parent, child;
    while (true) {
        set<int> leaves;
        cin >> T;
        if (T) {
            while (T--) {
                cin >> parent >> child;
                if (leaves.find(parent) != leaves.end())
                    leaves.erase(parent);   // parent node won't be a leaf node XD
                leaves.insert(child);
            }
            cin >> T;   // root is useless info.
            cout << leaves.size() << endl;
        } else
            return 0;
    }
}