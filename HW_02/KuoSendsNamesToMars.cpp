#include <iostream>
#include <string>
#define MAX 100000
using namespace std;

char str[MAX], stack[MAX];
int top(-1), length, cnt;
bool emptyFlag = false;

void Push(char x) { stack[++top] = x, emptyFlag = false; }
void Pop() { top--, cnt++, emptyFlag = true; }
void Empty() { top = -1; }

int main() {
    string input;
    cin >> input;
    length = input.length();
    for (int i = 0; i < length; i++)
        str[i] = input[i];   // string to char array

    for (int i = 0; i < length; i++) {
        if (!emptyFlag) {
            Push(str[i]);
            if (top == 0)
                continue;
            if (top == 1) {   // [0]和[1]比較
                if (stack[top] == stack[top - 1])
                    Pop();
            } else {          // 回文產生 := 是否和pre或pre-pre相同
                if (stack[top] == stack[top - 1] || stack[top] == stack[top - 2])
                    Pop();
            }
        } else {
            if (str[i] == stack[top]) {   // 即將Push的和top相同則又有回文
                cnt++;
                Empty();
                emptyFlag = false;
            } else {                      // 沒有回文不用++，清空後把新的當底
                Empty();
                Push(str[i]);
            }
        }
    }
    cout << cnt << endl;

    return 0;
}