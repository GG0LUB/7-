#include "array_based_polynomial.h"
#include <iostream>
#include <cstring>
#include <cmath>
#include <stdexcept>

#pragma warning(disable : 4996)

ArrayBasedPolynomial::ArrayBasedPolynomial(int degree, const double* coeffs)
    : Polynomial(degree, coeffs) {
    nonZeroCount_ = 0;
    for (int i = 0; i <= degree_; ++i) {
        if (coeffs[i] != 0) {
            ++nonZeroCount_;
        }
    }

    degrees_ = new int[nonZeroCount_];
    int index = 0;
    for (int i = 0; i <= degree_; ++i) {
        if (coeffs[i] != 0) {
            degrees_[index++] = i;
        }
    }
}

ArrayBasedPolynomial::~ArrayBasedPolynomial() {
    delete[] degrees_;
}

double ArrayBasedPolynomial::evaluate(double x) const {
    double result = 0.0;
    for (int i = 0; i < nonZeroCount_; ++i) {
        result += coefficients_[degrees_[i]] * std::pow(x, degrees_[i]);
    }
    return result;
}

char* ArrayBasedPolynomial::toString() const {
    static char result[512]; // ����������� ������ ��� �������� ����������
    result[0] = '\0';         // �������������� ������ ������

    for (int i = degree_; i >= 0; --i) {
        if (coefficients_[i] == 0.0) continue; // ���������� ������� ������������

        char buffer[50]; // ��������� ����� ��� �������� �����

        if (i != degree_) { // ��� �� ������� ����� ��������� "+" ��� "-"
            strcat(result, (coefficients_[i] > 0 ? "+" : "-"));
        }
        else if (coefficients_[i] < 0) { // ���� ������ ���� �������������
            strcat(result, "-");
        }

        // ��������� ������ ������������
        if (std::abs(coefficients_[i]) != 1.0 || i == 0) {
            snprintf(buffer, sizeof(buffer), "%.0f", std::abs(coefficients_[i]));
            strcat(result, buffer);
        }

        // ��������� "x" � �������, ���� ������� ������ 0
        if (i > 0) strcat(result, "x");
        if (i > 1) {
            snprintf(buffer, sizeof(buffer), "^%d", i);
            strcat(result, buffer);
        }
    }

    return result[0] == '\0' ? (char*)"0" : result; // ���� ������ �����, ���������� "0"
}
