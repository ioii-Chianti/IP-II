#include <stack>
#include <iostream>
#include "function.h"
using namespace std;
#define DEBUG 0

void printVec(list<State> List) {
    int i = 0;
    for (auto st: List) {
        cout << i++ << " path: ";
        for (auto v : st)
            cout << v << ' ';
        cout << endl;
    }
}

void printState(State s) {
    for (auto st: s) {
        cout << st << ' ';
    }cout << endl;
}

void Crossing::solve() {
    // int Min = 19991011;
    stack<State> dfs;
    State currentState;
    set<State> nextStates;
    list<State> path;
    _items.emplace_back(0);
    _items.emplace_back(0);
    _items.emplace_back(0);
    _items.emplace_back(1);
    dfs.emplace(_items);  // 放入初始狀

    int i = 0;
    while(!dfs.empty()) {
        if (DEBUG) cout << "------- loop: " << ++i << endl;
        currentState = dfs.top();

        // 如果這個 state 已經走過
        if (_explored.find(currentState) != _explored.end()) {
            if (DEBUG) cout << "- explored " << endl;
            dfs.pop();
            _explored.erase(currentState);
            path.pop_back();
            if (DEBUG) { cout << "- path " << endl; printVec(path); }
            continue;
        }
        if (DEBUG) cout << "- not explored " << endl;
        _explored.insert(currentState);
        path.emplace_back(currentState);
        if (DEBUG) { cout << "- path " << endl; printVec(path); }

        if (DEBUG) cout << "- found? " << found(currentState) << endl;
        if (found(currentState)) {
            _solutions.insert(path);
            if (DEBUG) cout << "- 111111 found, #sol " << _solutions.size() << endl;
        } else {
            nextStates = extend(currentState);
            for (auto st : nextStates) {
                if (valid(st)) {
                    dfs.emplace(st);
                    if (DEBUG) { cout << "- valid: "; printState(st); }
                }
            }
        }
    }
    if (DEBUG) cout << "- finish #sol " << _solutions.size() << endl;
}

set<State> Crossing::extend(State s) {
    return set<State>({ Go(s, 0, 0, 0), Go(s, 0, 0, 1), Go(s, 0, 1, 0), Go(s, 1, 0, 0) });
}

State Crossing::Go(State s, int wolf, int goat, int cabbage) {
    if (s[6] == 1) {
        s[0] -= wolf;
        s[1] -= goat;
        s[2] -= cabbage;
        s[3] += wolf;
        s[4] += goat;
        s[5] += cabbage;
    } else if (s[6] == -1) {
        s[0] += wolf;
        s[1] += goat;
        s[2] += cabbage;
        s[3] -= wolf;
        s[4] -= goat;
        s[5] -= cabbage;
    }
    s[6] = -(s[6]);
    return s;
}
bool Crossing::valid(State s) {
    // 遇過了
    if (_explored.find(s) != _explored.end())
        return false;
    // 超出範圍
    if (s[0] < 0 || s[1] < 0 || s[2] < 0 || s[3] < 0 || s[4] < 0 || s[5] < 0)
        return false;
    // 超出範圍
    if (s[0] > _items[0] || s[1] > _items[1] || s[2] > _items[2] || s[3] > _items[0] || s[4] > _items[1] || s[5] > _items[2])
        return false;
    // 被吃掉
    if (s[0] > s[1] && s[1] && s[6] != 1 || s[1] > s[2] && s[2] && s[6] != 1 || s[3] > s[4] && s[4] && s[6] != -1 || s[4] > s[5] && s[5] && s[6] != -1)
        return false;
    return true;
}
bool Crossing::found(State s) {
    // 左邊都沒東西了
    if (!s[0] && !s[1] && !s[2] /* && s[3] == _items[0] && s[4] == _items[1] && s[5] == _items[2] */ )
        return true;
    return false;
}