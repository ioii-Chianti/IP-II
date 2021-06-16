#include <iostream>
#include <set>
using namespace std;

int main() {
    int T, parent, child;
    while (true) {
        set<int> Set;
        cin >> T;
        if (T) {
            while (T--) {
                cin >> parent >> child;
                if (Set.find(parent) != Set.end())
                    Set.erase(parent);
                Set.insert(child);
            }
            cin >> T;
            cout << Set.size() << endl;
        } else
            return 0;
    }
    return 0;
}