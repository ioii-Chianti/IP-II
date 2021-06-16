#include <iostream>
#include <string>
#include <list>
using namespace std;

class Queue {
    public:
        // default constructor
        void Enqueue(int, int);
        void Dequeue();
    private:
        list<int> queue;
        list<int>::iterator last[3] = {queue.end(), queue.end(), queue.end()};
        // the last one of each country in the queue
};

int main() {
    int T, ID, nation;
    string operation;
    Queue Jinkela;

    cin >> T;
    while (T--) {
        cin >> operation;
        if (operation == "ENQUEUE") {
            cin >> ID;
            nation = ID % 3;
            Jinkela.Enqueue(ID, nation);
        } else if (operation == "DEQUEUE")
            Jinkela.Dequeue();
    }
    return 0;
}

void Queue::Enqueue(int ID, int nation) {
    if (last[nation] == queue.end()) {
        queue.emplace_back(ID);
        last[nation] = --queue.end();
    } else {  // 若不先記得 it 直接 ++last[nation] 的話，last 會跑錯位置
        list<int>::iterator it = last[nation];
        queue.emplace(++it, ID);   // 在 last 的下一個位置新增 ID
        last[nation]++;   // 再把 last 往後移
    }
}
void Queue::Dequeue() {
    if (!queue.empty()) {
        int ID = queue.front(), nation = ID % 3;
        if (ID == *last[nation])   // if this guy is the last of his country
            last[nation] = queue.end();
        cout << ID << endl;
        queue.pop_front();
    }
}