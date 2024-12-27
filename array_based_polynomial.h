#ifndef ARRAY_BASED_POLYNOMIAL_H
#define ARRAY_BASED_POLYNOMIAL_H

#include "polynomial.h"

class ArrayBasedPolynomial : public Polynomial {
public:
    ArrayBasedPolynomial(int degree, const double* coeffs);
    ~ArrayBasedPolynomial();

    int* getDegrees() const; // ���������� ������ ��������
    int getNonZeroCount() const; // ���������� ���������� ��������� �������������
    void displayDegrees() const; // �������� ������� ��������� �������������

    double evaluate(double x) const override; // ��������������� ������ evaluate

    char* toString() const override; // ��������������� toString


private:
    int* degrees_; // ������ ��� �������� �������� ��������� �������������
    int nonZeroCount_; // ���������� ��������� �������������
};

#endif // ARRAY_BASED_POLYNOMIAL_H
