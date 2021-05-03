#include <iostream>
#include <string>
#include "function.h"
using namespace oj;

Vector::Vector() {
    begin_ = new Int[0];
    end_ = begin_;
    last_ = begin_;
}

Vector::size_type Vector::capacity() const { return end_ - begin_; }
Vector::size_type Vector::size() const { return last_ - begin_; }
void Vector::pop_back() {
    if (size() > 0) last_--;
}

void Vector::push_back(value_type val) {
    size_type cap = capacity();
    if (size() == cap) {
        if (cap + 1 > cap * 3)
            reserve(cap + 1);
        else
            reserve(cap * 3);
        push_back(val);
    } else
        *(last_++) = val;
}

void Vector::insert(size_type pos,size_type count,value_type val) {
    
}