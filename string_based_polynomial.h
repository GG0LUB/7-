#ifndef STRING_BASED_POLYNOMIAL_H
#define STRING_BASED_POLYNOMIAL_H

#include "polynomial.h"

class StringBasedPolynomial : public Polynomial {
public:
    StringBasedPolynomial(int degree, const double* coeffs);
    ~StringBasedPolynomial();

    double* getCoefficients() const; // ���������� ������ �������������
    void displayCoefficients() const; // �������� ������������

    char* toString() const override; // ��������������� toString

private:
    double* coefficients_; // ������ ��� �������� �������������
    mutable char* polynomialString_; // ������ ������� ��� ������
};

#endif // STRING_BASED_POLYNOMIAL_H
