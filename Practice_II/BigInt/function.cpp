#include <iostream>
#include <string.h>
#include "function.h"
using namespace std;
#define BUG 1
// if (BUG) { cout << "--- " << endl; }

namespace oj {

    void add() {

    }
    void sub() {
        
    }

    BigInt::BigInt(char *s) {
        _val = new char[strlen(s) + 1]; // new [連續空間尺寸]{設值}，要用 delete[] 釋放
        strcpy(_val, s);
    }

    BigInt::~BigInt() { delete[] _val; }

    BigInt& BigInt::operator++() {
        add();
        if (BUG) cout << "--- last digit " << this->_val[strlen(_val) - 1] << endl;
        return *this;
    }
    BigInt BigInt::operator++(int) {
        BigInt ret = (*this);
        if (BUG) cout << "--- ret last " << ret._val[strlen(_val) - 1] << endl;
        add();
        if (BUG) cout << "--- this last " << this->_val[strlen(_val) - 1] << endl;
        return ret;
    }
    BigInt& BigInt::operator--() {
        this->_val[strlen(_val) - 1] -= 1;
        if (BUG) cout << "--- last digit " << this->_val[strlen(_val) - 1] << endl;
        return *this;
    }
    BigInt BigInt::operator--(int) {
        BigInt ret = (*this);
        if (BUG) cout << "--- ret last " << ret._val[strlen(_val) - 1] << endl;
        this->_val[strlen(_val) - 1] -= 1;
        if (BUG) cout << "--- this last " << this->_val[strlen(_val) - 1] << endl;
        return ret;
    }

    char *BigInt::to_s() {
        if (_val[0] != '0')
            return _val;
        else {
            int idx = 0;
            bool start = false;

            for (int i = 0; i < strlen(_val); i++) {
                if (_val[i] != '0' && !start)
                    start = true;   // ignore leading 0
                if (start)
                    _val[idx++] = _val[i];
            }
            _val[idx] = '\0';
            return _val;
        }
    }

}   // namespace

