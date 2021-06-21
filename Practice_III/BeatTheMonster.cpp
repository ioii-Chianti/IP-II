#include <iostream>
#include <queue>
#define DEBUG 1
#define DAMAGE 0
#define HEAL 1
using namespace std;

struct State {
    int level, hp, monster_hp;   // state tuple
    int rounds;   // distance from root
    State(int level, int hp, int monster_hp, int rounds = 0) : level(level), hp(hp), monster_hp(monster_hp), rounds(rounds) {}
    State() {};   // Struct doesn't have default constructor
    void print() { cout << " lv: " << this->level << " HP: " << this->hp << " monsHP: " << this->monster_hp << endl; }
};

bool visited[16][301][401] = {false};
int level_info[16][2];   // [level][DAMAGE] := damage, [level][HEAL] := healing

int main() {
    // input info.
    int max_level, max_hp, monster_hp, monster_dmg;
    cin >> max_level >> max_hp >> monster_hp >> monster_dmg;
    for (int i = 1; i <= max_level; i++)
        cin >> level_info[i][DAMAGE] >> level_info[i][HEAL];

    // init state into queue
    queue<State> bfs;
    bfs.push(State(1, max_hp, monster_hp));   // start with level 1, and both are max hp

    // BFS: Pop current node 的同時 push in 他的 children
    while (!bfs.empty()) {
        State cur_state = bfs.front(), next_state;
        bfs.pop();

        if (DEBUG) { cout << endl << "--- Pivot ::"; cur_state.print(); }

        // Calculate the next states
        cur_state.rounds++;

        // level up
        if (cur_state.level < max_level) {
            next_state = cur_state;
            next_state.level++;
            next_state.hp -= monster_dmg;
            // check validation and push
            if (next_state.hp > 0 && !visited[next_state.level][next_state.hp][next_state.monster_hp]) {
                visited[next_state.level][next_state.hp][next_state.monster_hp] = true;
                bfs.push(next_state);
                if (DEBUG) { cout << "- lv++ ::"; next_state.print(); }
            }
        }
        // attack
        next_state = cur_state;
        next_state.monster_hp -= level_info[next_state.level][DAMAGE];
        // player takes action first
        if (next_state.monster_hp <= 0) {
            bfs.push(next_state);
            break;
        }   // 怪獸先鼠掉惹，要先 push 這個 state 到 bfs.back() 再 break，啊不然就是 cur_state 要放到 while 外面然後印 cur_state.rounds
        next_state.hp -= monster_dmg;
        if (next_state.hp > 0 && !visited[next_state.level][next_state.hp][next_state.monster_hp]) {
            visited[next_state.level][next_state.hp][next_state.monster_hp] = true;
            bfs.push(next_state);
            if (DEBUG) { cout << "- attack ::"; next_state.print(); }
        }
        // heal
        next_state = cur_state;
        next_state.hp += level_info[next_state.level][HEAL];
        next_state.hp = next_state.hp > max_hp ? max_hp - monster_dmg : next_state.hp - monster_dmg;
        if (next_state.hp > 0 && !visited[next_state.level][next_state.hp][next_state.monster_hp]) {
            visited[next_state.level][next_state.hp][next_state.monster_hp] = true;
            bfs.push(next_state);
            if (DEBUG) { cout << "- heal ::"; next_state.print(); }
        }
    }  // end while

    if (bfs.empty())   // ended by while loop
        cout << -1 << endl;
    else               // ended by break
        cout << bfs.back().rounds << endl;
        
    return 0;
}