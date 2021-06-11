#include <iostream>
#include <string>
#include <queue>
using namespace std;

int main() {
    string operation;
    queue<string> Que;
    while (cin >> operation) {
        if (operation == "Push") {
            string name;
            cin >> name;
            Que.push(name);
        } else if (operation == "Pop") {
            if (!Que.empty())
                Que.pop();
        } else if (operation == "Front") {
            if (!Que.empty())
                cout << Que.front() << endl;
            else
                cout << "empty" << endl;
        }
    }
}