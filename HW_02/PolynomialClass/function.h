#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H
#include <iostream>

class Polynomial {

public:
    Polynomial();   // constructor 1
    Polynomial(const int, const int [51]);   // constructor 2

    Polynomial add(const Polynomial) const;  // add function
    Polynomial subtract(const Polynomial) const;  // subtract function
    Polynomial multiplication(const Polynomial) const;  // multiplication function
    void output() const;
private:
    int coefficients[101];   // integer coefficients
    int greatestPower;   // integer greatestPower

};

#endif

