#include <iostream>
#include <string>
#include <set>
using namespace std;
// Set notes in GitHub 'OuO'

int main() {
    int T;
    string operation;
    set<int, less<int>> Set;
    cin >> T;
    while (T--) {
        cin >> operation;
        if (operation == "insert") {
            int input;
            cin >> input;
            Set.insert(input);
        } else if (operation == "print") {
            set<int, less<int>>::iterator it, check;
            for (it = Set.begin(); it != Set.end(); it++) {
                check = it;
                check++;
                cout << *it << (check != Set.end() ? " " : "\n");
            }
        } else if (operation == "min") {
            if (Set.size())
                cout << *(Set.begin()) << endl;
        } else if (operation == "range_erase") {
            int left, right;
            cin >> left >> right;
            set<int, less<int>>::iterator Lit, Rit;
            // lower_bound and upper_bound are the same in singleSet
            Lit = Set.lower_bound(left);
            Rit = Set.upper_bound(right);
            Set.erase(Lit, Rit);   // [L, R)
        }
    }
    return 0;
}