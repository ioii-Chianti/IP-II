#include <stack>
#include <string>
#include "function.h"
using namespace std;

void Crossing::solve() {
    int Min = INT32_MIN;
    stack<State> StatesStack;   // 暫放過程中經過的 State，不符合可 POP 回歸最後只留下正確的樹枝
    State currentState;
    set<State> nextState;   // 用來放 extend
    list<State> currentPathes;   // 記錄過程中經過的 State
    // emplace_back := faster push_back
    _npeople.emplace_back(0);   // right missionary
    _npeople.emplace_back(0);   // right cannibal
    _npeople.emplace_back(1);   // boat's pos
    StatesStack.push(_npeople); // 初始狀態放進 Stack

    while (!StatesStack.empty()) {
        currentState = StatesStack.top();

        // 已經有找過這個 State，找到正確路徑後會清掉初始 State，結束迴圈
        if (_explored.find(currentState) != _explored.end()) {
            StatesStack.pop();
            _explored.erase(currentState);
            currentPathes.pop_back();
            continue;
        }
        _explored.insert(currentState);   // 把當前狀態放進發現過的 Set
        currentPathes.push_back(currentState);   // 走過的路徑

        if (found(currentState)) {    // 找到 Finish State 後儲存路徑、更新 Min
            _solutions.insert(currentPathes);
            Min = currentPathes.size() < Min ? currentPathes.size() : Min;
        } else {
            nextState = extend(currentState);   // Possible Actions
            for (State it : nextState) {
                if (valid(it))
                    StatesStack.push(it);
            }   // filter invalid actions，可能包含多個分支，但 Stack 會回朔到正確的分支
        }
    }

    // 清掉不是最短路徑的答案
    for (auto sol : _solutions) {
        if (sol.size() > Min)
            _solutions.erase(sol);
    }
}
// 延伸所有合法 Actions
set<State> Crossing::extend(State s) {
    return set<State>({Go(s, 0, 1), Go(s, 1, 0), Go(s, 1, 1), Go(s, 0, 2), Go(s, 2, 0)});
}
// 搭船過橋
State Crossing::Go(State s, int missionary, int cannibal) {
    if (s[4] == 1) {
        s[0] -= missionary;
        s[1] -= cannibal;
        s[2] += missionary;
        s[3] += cannibal;
    } else if (s[4] == -1) {
        s[0] += missionary;
        s[1] += cannibal;
        s[2] -= missionary;
        s[3] -= cannibal;
    }
    s[4] = -(s[4]);
    return s;
}
bool Crossing::valid(State s) {
    if (_explored.find(s) != _explored.end())
        return false;   // 已經出現過的 State
    if (s[0] < 0 || s[1] < 0 || s[2] < 0 || s[3] < 0)
        return false;   // 不合法的狀態
    if (s[0] && s[0] < s[1])
        return false;
    if (s[2] && s[2] < s[3])
        return false;   // 岸邊有傳教士且比食人族少
    return true;
}
bool Crossing::found(State s) {
    // Finish State
    if (!s[0] && !s[1])
        return true;
    return false;
}