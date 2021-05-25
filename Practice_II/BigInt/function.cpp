#include <cstring>
#include <cstdio>
#include "function.h"

namespace oj {

void swap(char *a, char *b) {
    char temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void reverse(char *s) {
    int len = strlen(s);
    for (int i = 0; i < len / 2; i++)
        swap(&(s[i]), &(s[len - 1 - i]));
}

BigInt::BigInt(char *s) {
    int len = strlen(s);
    _val = new char[1026]{'\0'};
    strcpy(_val, s);
}

BigInt::~BigInt() { delete _val; }

BigInt &BigInt::operator++() {
    reverse(_val);

    int len = strlen(_val);
    _val[0] += 1;
    for (int i = 0; i < len; i++) {
        if (_val[i] > '9') {
            // 超過必為10
            _val[i] = '0';
            // 如果已是最後一位，則新增一位並為1
            if (i == len - 1) {
                _val[i + 1] = '1';
                len++; // 記得增加長度
            } else // 如不是最後一位則上一位+1
                _val[i + 1] += 1;
        } else  // 沒有盡為之後跳出
            break;
    }
    _val[len + 1] = '\0';

    reverse(_val);
    return *this;
}

BigInt BigInt::operator++(int) {
    BigInt ret(_val);
    reverse(_val);

    int len = strlen(_val);
    _val[0] += 1;
    for (int i = 0; i < len; i++) {
        if (_val[i] > '9') {
            _val[i] = '0';
            if (i == len - 1) {
                _val[i + 1] = '1';
                len++;
            } else
                _val[i + 1] += 1;
        } else
            break;
    }
    _val[len + 1] = '\0';

    reverse(_val);
    return ret;
}
BigInt &BigInt::operator--() {
    reverse(_val);

    int len = strlen(_val);
    // 等於'0'
    if (len != 1 || _val[0] != '0') {
        _val[0] -= 1;
        for (int i = 1; i < len; i++) {
            if (_val[i - 1] < '0') {
                _val[i - 1] = '9';
                _val[i] -= 1;
            } else  // 沒有界為問題了則退出
                break;
        }
        // 如果最後一位是負的，則從高位數找到第一個0即為結束
        if (_val[len - 1] <= '0') {
            for (int i = len - 1; i > 0; i--) {
                if (_val[i] == '0')
                    _val[i] = '\0';
                else break;
            }
        }
    }
    reverse(_val);

    return (*this);
}

BigInt BigInt::operator--(int) {
    BigInt ret(_val);

    reverse(_val);

    int len = strlen(_val);
    if (len != 1 || _val[0] != '0') {
        _val[0] -= 1;
        for (int i = 1; i < len; i++) {
            if (_val[i - 1] < '0') {
                _val[i - 1] = '9';
                _val[i] -= 1;
            } else break;
        }
        if (_val[len - 1] <= '0') {
            for (int i = len - 1; i > 0; i--) {
                if (_val[i] == '0')
                    _val[i] = '\0';
                else break;
            }
        }
    }
    reverse(_val);
    return ret;
}
char *BigInt::to_s() { return _val; }

}   // end namespace