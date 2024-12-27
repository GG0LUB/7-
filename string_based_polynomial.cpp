#include "string_based_polynomial.h"
#include <iostream>
#include <cstring>
#include <cmath>
#include <stdexcept>

#pragma warning(disable : 4996)

StringBasedPolynomial::StringBasedPolynomial(int degree, const double* coeffs)
    : Polynomial(degree, coeffs), polynomialString_(nullptr) {
    coefficients_ = new double[length_];
    for (int i = 0; i <= degree_; ++i) {
        coefficients_[i] = coeffs[i];
    }
}

StringBasedPolynomial::~StringBasedPolynomial() {
    delete[] coefficients_;         // ����������� ������ ��� �������������
    delete[] polynomialString_;     // ����������� ������ ��� ������
}

double* StringBasedPolynomial::getCoefficients() const {
    return coefficients_;
}

void StringBasedPolynomial::displayCoefficients() const {
    std::cout << "Coefficients: ";
    for (int i = 0; i <= degree_; ++i) {
        std::cout << coefficients_[i] << " ";
    }
    std::cout << std::endl;
}

char* StringBasedPolynomial::toString() const {
    static char result[512]; // ����������� ������ ��� ����������
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

        // ��������� ������ ������������, ������ ���� ��� �� "1x"
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

    return result[0] == '\0' ? (char*)"0" : result; // ���������� "0", ���� ������ �����
}
