#ifndef ARRAY_BASED_POLYNOMIAL_H
#define ARRAY_BASED_POLYNOMIAL_H

#include "polynomial.h"

class ArrayBasedPolynomial : public Polynomial {
public:
    ArrayBasedPolynomial(int degree, const double* coeffs);
    ~ArrayBasedPolynomial();

    int* getDegrees() const; // Возвращает массив степеней
    int getNonZeroCount() const; // Возвращает количество ненулевых коэффициентов
    void displayDegrees() const; // Печатает степени ненулевых коэффициентов

    double evaluate(double x) const override; // Переопределение метода evaluate

    char* toString() const override; // Переопределение toString


private:
    int* degrees_; // Массив для хранения степеней ненулевых коэффициентов
    int nonZeroCount_; // Количество ненулевых коэффициентов
};

#endif // ARRAY_BASED_POLYNOMIAL_H
