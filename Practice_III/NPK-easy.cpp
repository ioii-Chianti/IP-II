#include <iostream>
#include <string>
#include <list>
using namespace std;

enum { America, Africa, Japan };

int main() {
    int T, ID, nation, last[3] = {-1, -1, -1};
    string operation;
    list<int> queue;

    cin >> T;
    while (T--) {
        cin >> operation;
        if (operation == "ENQUEUE") {
            cin >> ID;
            nation = ID % 3;
            if (last[nation] == -1) {
                queue.emplace_back(ID);
                last[nation] = ID;
            }
                
            else {
                list<int>::iterator it;
                for (it = queue.begin(); it != queue.end(); it++) {
                    if (*it == last[nation]) {
                        queue.emplace(++it, ID);
                        last[nation] = ID;
                        break;
                    }
                }
            }
        } else if (operation == "DEQUEUE") {
            if (!queue.empty()) {
                cout << queue.front() << endl;
                queue.pop_front();
            }
        }
    }
    return 0;
}