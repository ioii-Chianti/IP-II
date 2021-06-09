#include <iostream>
#include <string>
#include <stack>
using namespace std;

bool parenChecker(string paren) {
    stack<char> Stack;
    bool ret;
    for (char ch : paren) {
        if (ch == '<' || ch == '(' || ch == '[' || ch == '{')
            Stack.push(ch);
        else {
            if (Stack.empty())
                return false;
            switch (ch) {
                case '>':
                    if (Stack.top() == '<') {
                        Stack.pop();
                        break;
                    }
                    return false;
                case ')':
                    if (Stack.top() == '(') {
                        Stack.pop();
                        break;
                    }
                    return false;
                case ']':
                    if (Stack.top() == '[') {
                        Stack.pop();
                        break;
                    }
                    return false;
                case '}':
                    if (Stack.top() == '{') {
                        Stack.pop();
                        break;
                    }
                    return false;
            }
        }
    }
    return Stack.size() == 0;
}

int main() {
    int T;
    string paren;
    cin >> T;
    cin.ignore();
    for (int i = 1; i <= T; i++) {
        getline(cin, paren);
        cout << "Case " << i << ": " << (parenChecker(paren) ? "Yes" : "No") << endl;
    }
    return 0;
}