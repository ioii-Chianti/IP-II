#include <iostream>
#include <queue>
#include <set>
#define DEBUG 1
using namespace std;

int const correctBoard[9] = {1, 2, 3, 4, 5, 6, 7, 8, 0};
int ans = 15;

struct State {
    int board[9], index, steps;
    State(int *arr, int step = 0) : steps(step) {
        for (int i = 0; i < 9; i++) {
            board[i] = arr[i];
            if (board[i] == 0)
                index = i;
        }
    }
    State() {};
    void print() {
        for (int i = 0; i < 9; i++)
            cout << this->board[i] << ' ';
        cout << endl;
    }
    bool correct() {
        for (int i = 0; i < 9; i++)
            if (this->board[i] != correctBoard[i])
                return false;
        return true;
    }
    bool operator<(State const &state) const { return index < state.index; }
};

int main() {
    int T;
    cin >> T;
    while (T--) {
        int board[9];
        for (int i = 0; i < 9; i++)
            cin >> board[i];
        
        queue<State> bfs;
        set<State> visited;
        bfs.push(State(board));
        visited.insert(State(board));

        while (!bfs.empty()) {
            State cur_state = bfs.front(), next_state;
            bfs.pop();

            if (cur_state.correct()) {
                bfs.push(cur_state);
                if (DEBUG) cout << "- found in " << cur_state.steps << endl;
                break;
            }

            if (DEBUG) { cout << "- "; cur_state.print(); }

            int row = cur_state.index / 3;
            int col = cur_state.index % 3;

            cur_state.steps++;

            if (row != 0) {
                next_state = cur_state;
                int toMove = next_state.board[next_state.index - 3];
                if (DEBUG) { cout << "- to move "<< toMove << endl; }
                next_state.board[next_state.index] = toMove;
                next_state.board[next_state.index - 3] = 0;
                next_state.index -= 3;
                if (visited.find(next_state) == visited.end()) {
                    visited.insert(next_state);
                    bfs.push(next_state);
                    if (DEBUG) { cout << "- up "; next_state.print(); }
                }
            }

            if (row != 2) {
                next_state = cur_state;
                int toMove = next_state.board[next_state.index + 3];
                next_state.board[next_state.index] = toMove;
                next_state.board[next_state.index + 3] = 0;
                next_state.index += 3;
                if (visited.find(next_state) == visited.end()) {
                    visited.insert(next_state);
                    bfs.push(next_state);
                    if (DEBUG) { cout << "- down "; next_state.print(); }
                }
            }

            if (col != 0) {
                next_state = cur_state;
                int toMove = next_state.board[next_state.index - 1];
                next_state.board[next_state.index] = toMove;
                next_state.board[next_state.index - 1] = 0;
                next_state.index--;
                if (visited.find(next_state) == visited.end()) {
                    visited.insert(next_state);
                    bfs.push(next_state);
                    if (DEBUG) { cout << "- left "; next_state.print(); }
                }
            }

            if (col != 2) {
                next_state = cur_state;
                int toMove = next_state.board[next_state.index + 1];
                next_state.board[next_state.index] = toMove;
                next_state.board[next_state.index + 1] = 0;
                next_state.index++;
                if (visited.find(next_state) == visited.end()) {
                    visited.insert(next_state);
                    bfs.push(next_state);
                    if (DEBUG) { cout << "- right "; next_state.print(); }
                }
            }
        }   // end bfs loop
        if (bfs.empty() || bfs.back().steps > 14) {
            cout << "em " << bfs.empty() << endl;
            cout << "You'd better skip this game." << endl;
        }
            
        else
            cout << "You can solve it within " << bfs.back().steps << " steps." << endl;
    }   // end T loop
    return 0;
}