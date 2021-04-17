#include <iostream>
#include <string>
#include "function.h"
using namespace std;

Polynomial::Polynomial() {}
Polynomial::Polynomial(const int power, const int cof[51]) {
    this->greatestPower = power;
    for (int i = power; i >= 0; i--)
        this->coefficients[i] = cof[i];
}   // put input into object's attributes

Polynomial Polynomial::add(Polynomial Py) const {
    Polynomial Px = *this;   // obj who calls this method
    int PxPower = Px.greatestPower;
    int PyPower = Py.greatestPower;
    int newPower = PxPower > PyPower ? PxPower : PyPower;
    Px.greatestPower = newPower;   // highest power

    for (int i = newPower; i >=0; i--) {
        if (i == PyPower) {   // add coefs when two powers are the same
            Px.coefficients[i] += Py.coefficients[i];
            PyPower--;        // both decrease
        }
    }
    return Px;
}

Polynomial Polynomial::subtract(Polynomial Py) const {
    Polynomial Px = *this;   // obj who calls this method
    int PxPower = Px.greatestPower;
    int PyPower = Py.greatestPower;
    int newPower = PxPower > PyPower ? PxPower : PyPower;
    Px.greatestPower = newPower;   // highest power

    for (int i = newPower; i >=0; i--) {
        if (i == PyPower) {   // substract coefs when two powers are the same
            Px.coefficients[i] -= Py.coefficients[i];
            PyPower--;        // both decrease
        }
    }
    return Px;
}

Polynomial Polynomial::multiplication(Polynomial Py) const {
    Polynomial Px = *this;
    int PxPower = Px.greatestPower;
    int PyPower = Py.greatestPower;
    int newPower = PxPower + PyPower;
    int newCof[105] = {0};

    Px.greatestPower = newPower;
    for (int i = 0; i <= PxPower; i++)
        for (int j = 0; j <= PyPower; j++)
            newCof[i + j] += Px.coefficients[i] * Py.coefficients[j];
            // 係數相乘指數相加
    
    for (int i = 0; i <= newPower; i++)
        Px.coefficients[i] = newCof[i];
        // renew coef

    return Px;
}

void Polynomial::output() const {
    for (int i = this->greatestPower; i > 0; i--)
        cout << this->coefficients[i] << " ";
    cout << this->coefficients[0];
}