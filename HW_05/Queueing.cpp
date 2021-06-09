#include <iostream>
#include <string>
#include <queue>
using namespace std;

int main() {
    queue<string> Queue;
    string operation;
    while (cin >> operation) {
        if (operation == "Push") {
            string name;
            cin >> name;
            Queue.push(name);
        } else if (operation == "Pop")
            if (!Queue.empty())
                Queue.pop();
        else if (operation == "Front")
            if (!Queue.empty())
                cout << Queue.front() << endl;
            else cout << "empty" << endl;
    }
    return 0;
}