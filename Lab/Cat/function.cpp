#include<iostream>
#include<string>
#include"function.h"
using namespace std;

big_number:: big_number(string num) {
    this->num = num;
    // cout << num;
}

bool big_number::multiple_of_two() {
    int len = (this->num).length();
    if (this->num[len - 1 ] == '0' || this->num[len - 1] == '2' || this->num[len - 1] == '4' || this->num[len - 1] == '6'|| this->num[len - 1] == '8')
        return true;
    return false;
}

bool big_number::multiple_of_three() {
    int len = (this->num).length();
    int Sum = 0;
    for (int i = 0; i < len; i++)
        Sum += (this->num[i] - '0');
    if (Sum % 3)
        return false;
    else
        return true;
}

bool big_number::multiple_of_four() {
    int len = (this->num).length();
    int Sum = ( this->num[len - 2] - '0') * 10 + (this->num[len - 1] - '0');
    if (Sum % 4)
        return false;
    else
        return true;
}

bool big_number::multiple_of_five() {
    int len = (this->num).length();
    if (this->num[len - 1] == '0' || this->num[len - 1] == '5')
        return true;
    return false;
}
bool big_number::multiple_of_six() {
    if (this->multiple_of_two() && this->multiple_of_three())
        return true;
    return false;
}

bool big_number::multiple_of_eight() {
    int len = (this->num).length();
    int Sum = (this->num[len - 3] - '0') * 100 + (this->num[len - 2] - '0') * 10 + (this->num[len - 1] - '0');
    if (Sum % 8)
        return false;
    else
        return true;
}

bool big_number::multiple_of_nine() {
    int len = (this->num).length();
    int Sum = 0;
    for (int i = 0; i < len; i++)
        Sum += (this->num[i] - '0');
    if (Sum % 9)
        return false;
    else
        return true;
}

bool big_number::multiple_of_ten() {
    int len = (this->num).length();
    if (this->num[len - 1] == '0')
        return true;
    return false;
}
bool big_number::multiple_of_eleven() {
    int len = (this->num).length();
    int Sum = 0;
    for (int i = 0; i < len; i++) {
        if (i % 2 == 0) {
            Sum += (this->num[i] - '0');
        } else {
            Sum -= (this->num[i] - '0');
        }
    }
    if (Sum % 11 == 0)
        return true;
    return false;
}