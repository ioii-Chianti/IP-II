#include <iostream>
#include <string>
#define MAX 100000
using namespace std;

int top(-1), cnt = 0, length;
bool flag = false;

char *stack;
bool isEmpty() { return (top == -1); }
void Push(char x) { stack[++top] = x, flag = false; }
void Pop() { top--, cnt++, flag = true; }
void Empty() {
    for (int i = 0; i < length; i++)
        stack[i] = '\0';
    top = -1;
}

int main() {
    string input;
    cin >> input;
    length = input.length();
    char str[length];
    for (int i = 0; i < length; i++)
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

        if (top == 0)
            continue;
        else if (top == 1) {
            if (stack[top] == stack[top - 1])
				Pop();
        } else {
            if (stack[top] == stack[top - 1] || stack[top] == stack[top - 2])
                Pop();
        }
    }
    cout << cnt << endl;

    return 0;
}