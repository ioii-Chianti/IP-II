#include <iostream>
#include <string>
#define MAX 100000
using namespace std;

int top(-1), cnt;
bool flag = false;

char *stack;
bool isEmpty() { return (top == -1); }
void Push(int x) { stack[++top] = x, flag = false; }
void Pop() { top--, cnt++, flag = true; }
void Empty() { top = -1; }

int main() {
    string input;
    cin >> input;
    int length = input.length();
    char str[length];
    for (int i = 0; i < sizeof(str); i++)
        str[i] = input[i];
    char *stack = new char(length);

    Push(str[0]);
    Push(str[1]);

    if (str[0] == str[1])
        Pop();

    for (int i = 2; i < length; i++) {
        if (flag) {
            if (str[i] == stack[top]) {
                cnt++;
                Empty();
                flag = false;
            } else {
                Empty();
                Push(str[i]);
            }
            continue;
        }
        Push(str[i]);

        if (top)
            if (stack[top] == stack[top - 1] || stack[top] == stack[top - 2])
                Pop();
    }
    cout << cnt << endl;

    return 0;
}