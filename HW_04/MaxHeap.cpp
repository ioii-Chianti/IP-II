#include <iostream>
#include <vector>
#include <string>
#define DEBUG 0
using namespace std;

void printInfo(const vector<int> vec) {
    cout << "--- con: ";
    for (vector<int>::const_iterator it = vec.begin(); it != vec.end(); it++)
        cout << *it << " ";
    cout << endl << "--- size: " << vec.size() << endl;
    cout << "--- cap: "<< vec.capacity() << endl;
}   // for debugging

void Swap(int &x, int &y) {
    int temp = x;
    x = y;
    y = temp;
}   // call by ref.

void Heapify(vector<int> &vec, int index, const string op) {
    if (op == "PUSH") {
        // cur node is root
        if (index == 1)
            return;
        // parent node < cur node
        if (vec[index / 2] < vec[index]) {
            Swap(vec[index / 2], vec[index]);
            Heapify(vec, index / 2, op);
        } else return;   // in correct pos
    } else if (op == "POP") {
        int maxIndex;
        // cur node is leaf
        if (2 * index >= vec.size())
            return;
        else if (2 * index + 1 >= vec.size())
            maxIndex = 2 * index;
        else   // cur has two children
            maxIndex = vec[2 * index] > vec[2 * index + 1] ? 2 * index : 2 * index + 1;
        
        if (vec[index] < vec[maxIndex]) {
            Swap(vec[index], vec[maxIndex]);
            Heapify(vec, maxIndex, op);
        } else return;   // in correct pos
    }
}

int main() {
    string operation;
    vector<int> maxHeap;
    maxHeap.push_back(0);
    while (cin >> operation) {
        if (operation == "PUSH") {
            int input;
            cin >> input;
            // push then rearrange
            maxHeap.push_back(input);
            Heapify(maxHeap, maxHeap.size() - 1, operation);
            if (DEBUG) printInfo(maxHeap);
        } else if (operation == "POP") {
            if (maxHeap.size() == 1)
                continue;
            // put the pop node in last pos 
            Swap(maxHeap[1], maxHeap[maxHeap.size() - 1]);
            // pop then rearrange
            maxHeap.pop_back();
            Heapify(maxHeap, 1, operation);
            if (DEBUG) printInfo(maxHeap);
        } else if (operation == "TOP") {
            if (maxHeap.size() == 1)
                cout << "Null" << endl;
            else
                cout << maxHeap[1] << endl;
        }
    }
    return 0;
}