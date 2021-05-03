#include <iostream>
#include <string.h>
#include "function.h"
using namespace std;

special_power::special_power(int n) { this->n = n; }
int special_power::fpow(int x) {
    if (x == 1) return 1;
    long long product = 1;
    int power = n;
    while (power--)
        product *= x;
    product %= 880301;
    return (int)product;
}
int special_power::fpow(int x, int m) {
    if (x == 1) return 1;
    long long product = 1;
    int power = n;
    while (power--)
        product *= x;
    product %= m;
    return (int)product;
}
int special_power::fpow() {
    long long product = 1;
    int power = n;
    while (power--)
        product *= 2;
    product %= 880301;
    return (int)product;
}
string special_power::fpow(string s) {
    string str;
    int pow;
    for (int i = 0; i < s.length(); i++) {
        pow = n;
        while (pow--)
            str += s[i];
    }
    return str;
}
string special_power::fpow(string s, int m) {
    string str;
    int pow;
    for (int i = 0; i < s.length(); i++) {
        pow = n;
        while (pow--) {
            str += s[i];
            if (str.length() == m)
                return str;
        }
    }
    return str;
}