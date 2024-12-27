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
    delete[] coefficients_;         // Освобождаем память для коэффициентов
    delete[] polynomialString_;     // Освобождаем память для строки
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
    static char result[512]; // Статический массив для результата
    result[0] = '\0';         // Инициализируем пустую строку

    for (int i = degree_; i >= 0; --i) {
        if (coefficients_[i] == 0.0) continue; // Пропускаем нулевые коэффициенты

        char buffer[50]; // Временный буфер для текущего члена

        if (i != degree_) { // Для не первого члена добавляем "+" или "-"
            strcat(result, (coefficients_[i] > 0 ? "+" : "-"));
        }
        else if (coefficients_[i] < 0) { // Если первый член отрицательный
            strcat(result, "-");
        }

        // Добавляем модуль коэффициента, только если это не "1x"
        if (std::abs(coefficients_[i]) != 1.0 || i == 0) {
            snprintf(buffer, sizeof(buffer), "%.0f", std::abs(coefficients_[i]));
            strcat(result, buffer);
        }

        // Добавляем "x" и степень, если степень больше 0
        if (i > 0) strcat(result, "x");
        if (i > 1) {
            snprintf(buffer, sizeof(buffer), "^%d", i);
            strcat(result, buffer);
        }
    }

    return result[0] == '\0' ? (char*)"0" : result; // Возвращаем "0", если строка пуста
}
