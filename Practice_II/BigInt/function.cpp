#include <iostream>
#include <string.h>
#include "function.h"
using namespace std;

namespace oj {

BigInt::BigInt(char *s) {
    int i;
    for (i = 0; i < strlen(s); i++)
        _val[i] = s[i];
    _val[i] = '\0';
}

BigInt::~BigInt() {}

BigInt& BigInt::operator++();
BigInt BigInt::operator++(int);
BigInt& BigInt::operator--();
BigInt BigInt::operator--(int);

char *BigInt::to_s() { return _val; }
}

