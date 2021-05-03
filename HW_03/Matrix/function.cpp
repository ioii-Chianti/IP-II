#include <iostream>
#include <string>
#include "function.h"
using namespace std;

// 參數預設值只需在宣告時寫出，但定義有註解較佳
Matrix::Matrix(int s /* = 5*/) {
    size = s;
    matrix = new int *[size];
    for (int i = 0; i < size; i++)
        matrix[i] = new int[size];
    buf = new int[size * size];
}

// Copy constructor
Matrix::Matrix(const Matrix &existMatrix) {
    size = existMatrix.size;
    matrix = existMatrix.matrix;
    buf = existMatrix.buf;
}

Matrix::~Matrix() {
    for (int i; i < size; i++)
        delete[] matrix[i];
    delete[] matrix;
}

// different from copy constructor, give scalars but not pointers
Matrix& Matrix::operator=(const Matrix &a) {
    size = a.size;
    for (int i = 0, idx = 0; i < size; i++)
        for (int j = 0; j < size; j++) {
            matrix[i][j] = a.matrix[i][j];
            buf[idx++] = matrix[i][j];
        }
    return *this;   // return modified version of this
}

Matrix& Matrix::clockwise90() {
    int idx = 0;
    Matrix origin(size);
    origin = *this;   // init then give

    // renew matrix
    for (int i = 0; i < size; i++) {
        for (int j = size - 1; j >= 0; j--)
            matrix[i][idx++] = origin.matrix[j][i];
        idx = 0;
    }
    // renew buf
    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            buf[idx++] = matrix[i][j];

    return *this;   // return modified version of this
}

std::ostream &operator<<(std::ostream &stream, const Matrix &mx) {
    for (int i = 0; i < mx.size; i++)
        for (int j = 0; j < mx.size; j++)
            cout << mx.matrix[i][j] << (j != mx.size - 1 ? " " : "\n");
    return stream;   // return to cout as ostream, so that the next '<<' will be treated as normal '<<'
}

std::istream &operator>>(std::istream &stream, Matrix &mx) {
    for (int i = 0, idx = 0; i < mx.size; i++)
        for (int j = 0; j < mx.size; j++) {
            cin >> mx.buf[idx++];
            mx.matrix[i][j] = mx.buf[idx - 1];
        }
    return stream;   // return to cin as istream, so that the next '>>' will be treated as normal '>>'
}