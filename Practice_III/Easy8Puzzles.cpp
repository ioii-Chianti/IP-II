#include <iostream>
#include <vector>
#include <stack>
using namespace std;
using Board = vector<vector<int>>;

Board correctBoard = {{1, 2, 3}, {4, 5, 6}, {7, 8, 0}};

// Declaration
class Grid {
    public:
        Grid();
        void Play();
        bool isCorrect();
        void Result();
    private:
        Board board;
        int MinSteps;
};

// Main
int main() {
    int T;
    cin >> T;
    while (T--) {
        Grid grid = Grid();
        grid.Play();
        grid.Result();
    }
    return 0;
}

// Definition
Grid::Grid() {
    int input;
    vector<int> row;
    for (int i = 0; i < 3; i++) {
        row.clear();
        for (int j = 0; j < 3; j++) {
            cin >> input;
            row.emplace_back(input);
        }
        this->board.emplace_back(row);
    }
    cout << "init end\n";
}

void Grid::Play() {
    cout << "Playing...\n";
}

bool Grid::isCorrect() { return correctBoard == this->board; }

void Grid::Result() {
    if (this->MinSteps > 14)
        cout << "You'd better skip this game." << endl;
    else
        cout << "You can solve it within " << this->MinSteps << " steps." << endl;
}