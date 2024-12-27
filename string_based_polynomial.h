#ifndef STRING_BASED_POLYNOMIAL_H
#define STRING_BASED_POLYNOMIAL_H

#include "polynomial.h"

class StringBasedPolynomial : public Polynomial {
public:
    StringBasedPolynomial(int degree, const double* coeffs);
    ~StringBasedPolynomial();

    double* getCoefficients() const; // Возвращает массив коэффициентов
    void displayCoefficients() const; // Печатает коэффициенты

    char* toString() const override; // Переопределение toString

private:
    double* coefficients_; // Массив для хранения коэффициентов
    mutable char* polynomialString_; // Хранит полином как строку
};

#endif // STRING_BASED_POLYNOMIAL_H
