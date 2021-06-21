#include <iostream>
#include <vector>
#include <list>
#include <algorithm>
using namespace std;

int main() {
    ios::sync_with_stdio(0); cin.tie(0);
    int N, len, input, Max, flag = 0;
    list<int> seq;
    cin >> N >> len;
    for (int i = 0; i < N; i++) {
        cin >> input;
        seq.emplace_back(input);
        if (!flag && seq.size() == len) {
            Max = *max_element(seq.begin(), seq.end());
            flag = 1;
        } else if (flag) {
            if (Max != seq.front()) {
                Max = input > Max ? input : Max;
                seq.pop_front();
            } else {
                seq.pop_front();
                // cout << "seq: ";
                // for (auto i : seq)
                //     cout << i << ' ';
                // cout << "\n";
                Max = *max_element(seq.begin(), seq.end());
            }
        }
        if (flag) cout << Max << ' ';
    }
    cout << '\n';
    return 0;
}