#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include "function.h"
using namespace std;

void RleCodec::encode() {
    stringstream ss;
    int cnt = 0;
    char ch = code_str[0];
    for (int i = 0; code_str[i] != '\0'; i++) {
        if (code_str[i] == ch)
            cnt++;
        else {
            if (cnt == 1)
                ss << ch;
            else if (cnt == 2)
                ss << ch << ch;
            else if (cnt > 2)
                ss << cnt << ch;
            ch = code_str[i];
            cnt = 1;
        }
    }
    if (cnt == 1)
        ss << ch;
    else if (cnt ==2)
        ss << ch << ch;
    else if (cnt > 2)
        ss << cnt << ch;
    code_str = ss.str();
    encoded = true;
}

void RleCodec::decode() { }