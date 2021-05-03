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
    int idx = 0;
    size = a.size;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            matrix[i][j] = a.matrix[i][j];
            buf[idx++] = matrix[i][j];
        }
    }
    return *this;   // return modified version of this
}

Matrix& Matrix::clockwise90() {
    int idx = 0;
    Matrix origin(size);
    origin = *this;   // init then give
    
    for (int i = 0; i < size; i++) {
        for (int j = size - 1; j >= 0; j--)
            matrix[i][idx++] = origin.matrix[j][i];
        idx = 0;
    }

    for (int i = 0; i < size; i++)
        for (int j = 0; j < size; j++)
            buf[idx++] = matrix[i][j];

    return *this;
}

std::ostream &operator<<(std::ostream &stream, const Matrix &mat) {
    for (int i = 0; i < mat.size; i++) {
        for (int j = 0; j < mat.size; j++) {
            cout << mat.matrix[i][j];
            if (j != mat.size - 1)
                cout << " ";
            else
                cout << endl;
        }
    }
    return stream;
}

std::istream &operator>>(std::istream &stream, Matrix &mat) {
    int x = 0, y = 0;
    for (int i = 0; i < mat.size * mat.size; i++) {
        cin >> mat.buf[i];
        mat.matrix[x][y++] = mat.buf[i];
        if (y == mat.size)
            x++, y = 0;
    }
    return stream;
}