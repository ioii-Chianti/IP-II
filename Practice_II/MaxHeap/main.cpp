#include <iostream>
#include <string>
#include "function.cpp"
using namespace std;

int main() {
    int T, toPush;
    Array_MAX_HEAP A_heap;
    List_MAX_HEAP B_heap;
    string operation;
    cin >> T;
    while (T--) {
        cin >> operation;
        if (operation == "A_push") {
            cin >> toPush;
            A_heap.PUSH(toPush);
        } else if (operation == "L_push") {
            cin >> toPush;
            B_heap.PUSH(toPush);
        } else if (operation == "max") {
            cout << A_heap.MAX() << "\n";
            cout << B_heap.MAX() << "\n";
        } else if (operation == "A_pop") {
            cout << A_heap.POP() << "\n";
        } else if (operation == "L_pop") {
            cout << B_heap.POP() << "\n";
        } else if (operation == "size") {
            cout << A_heap.count() << "\n";
            cout << B_heap.count() << "\n";
        }
    }
}