#include "polynomial.h"
#include <cstdio>
#include <cmath>
#include <cstring>
#include <stdexcept>
#include <iostream>
#include <vector>
#include <sstream>
#include <string>
#include <sstream> // ��� ���������� ������

#pragma warning(disable : 4996)

// ������������� ������������ ��������
int Polynomial::count_ = 0;

Polynomial::Polynomial() : degree_(0), length_(1) {
    coefficients_ = new double[length_] {0.0};
    count_++;
    std::cout << "Polynomial created (default constructor). Current count: " << count_ << std::endl;
}

Polynomial::Polynomial(int degree, const double* coeffs) : degree_(degree), length_(degree + 1) {
    coefficients_ = new double[length_];
    for (int i = 0; i < length_; ++i) {
        coefficients_[i] = coeffs[i];
    }
    count_++;
    std::cout << "Polynomial created (parameterized constructor). Current count: " << count_ << std::endl;
}

Polynomial::Polynomial(const Polynomial& other) : degree_(other.degree_), length_(other.length_) {
    coefficients_ = new double[length_];
    for (int i = 0; i < length_; ++i) {
        coefficients_[i] = other.coefficients_[i];
    }
    count_++;
    std::cout << "Polynomial copied. Current count: " << count_ << std::endl;
}

Polynomial::~Polynomial() {
    delete[] coefficients_;
    count_--;
    std::cout << "Polynomial destroyed. Current count: " << count_ << std::endl;
}

// ����� getDegree
int Polynomial::getDegree() const {
    return degree_;
}

// ����� evaluate
double Polynomial::evaluate(double x) const {
    if (!coefficients_) {
        throw std::runtime_error("Polynomial coefficients are not initialized.");
    }
    double result = 0.0;
    for (int i = 0; i <= degree_; ++i) {
        result += coefficients_[i] * std::pow(x, i);
    }
    return result;
}

// ���������� ���������� ��������� ��������
int Polynomial::getCount() {
    return count_;
}

Polynomial Polynomial::operator-(const Polynomial& other) const {
    int maxDegree = std::max(degree_, other.degree_);
    double* newCoeffs = new double[maxDegree + 1]();

    for (int i = 0; i <= degree_; i++) {  // ������ � degree_
        newCoeffs[i] += coefficients_[i];
    }
    for (int i = 0; i <= other.degree_; i++) {  // ������ � degree_
        newCoeffs[i] -= other.coefficients_[i];
    }

    Polynomial result(maxDegree, newCoeffs);
    delete[] newCoeffs;
    return result;
}

Polynomial& Polynomial::operator++() {
    double* newCoeffs = new double[length_ + 1];
    newCoeffs[0] = 0.0;
    for (int i = 0; i < length_; i++) {
        newCoeffs[i + 1] = coefficients_[i];
    }
    delete[] coefficients_;
    coefficients_ = newCoeffs;
    degree_++;  // ������ � degree_
    length_++;
    return *this;
}

Polynomial Polynomial::operator++(int) {
    Polynomial temp = *this;
    ++(*this);
    return temp;
}

Polynomial& Polynomial::operator--() {
    if (degree_ == 0) throw std::underflow_error("Cannot decrement degree of a zero-degree polynomial");

    double* newCoeffs = new double[length_ - 1];
    for (int i = 0; i < length_ - 1; i++) {  // ������ � degree_
        newCoeffs[i] = coefficients_[i + 1];
    }
    delete[] coefficients_;
    coefficients_ = newCoeffs;
    degree_--;  // ������ � degree_
    length_--;
    return *this;
}

Polynomial Polynomial::operator--(int) {
    Polynomial temp = *this;
    --(*this);
    return temp;
}

double Polynomial::operator()(double x) const {
    return evaluate(x);
}

double& Polynomial::operator[](int index) {
    if (index < 0 || index >= length_) throw std::out_of_range("Index out of range");
    return coefficients_[index];
}

Polynomial& Polynomial::operator=(const Polynomial& other) {
    if (this == &other) return *this;  // ������ �� ����������������

    delete[] coefficients_;

    degree_ = other.degree_;  // ������ � degree_
    length_ = other.length_;
    coefficients_ = new double[length_];
    for (int i = 0; i < length_; i++) {
        coefficients_[i] = other.coefficients_[i];
    }

    return *this;
}

// ���������� ��������� ����� (���������� ����������)
std::istream& operator>>(std::istream& is, Polynomial& p) {
    // ������� ������� �������������
    delete[] p.coefficients_;

    std::vector<double> coeffs; // ��������� ��������� �������������
    int maxDegree = 0;

    char line[256];
    is.getline(line, sizeof(line)); // ������ ��� ������, ���������� ���������
    std::istringstream iss(line);

    while (!iss.eof()) {
        double coeff;
        char x;
        char caret;
        int degree;

        if (!(iss >> coeff)) break; // ������ ������������
        if (!(iss >> x) || x != 'x') break; // ������ 'x'
        if (!(iss >> caret) || caret != '^') break; // ������ '^'
        if (!(iss >> degree)) break; // ������ �������

        if (degree < 0) {
            throw std::runtime_error("������� �� ����� ���� �������������.");
        }

        if (degree >= coeffs.size()) {
            coeffs.resize(degree + 1, 0.0);
        }
        coeffs[degree] = coeff;
        maxDegree = std::max(maxDegree, degree);
    }

    p.degree_ = maxDegree;  // ������ � degree_
    p.length_ = coeffs.size();
    p.coefficients_ = new double[p.length_];
    for (int i = 0; i < p.length_; ++i) {
        p.coefficients_[i] = coeffs[i];
    }

    return is;
}

// ���������� ��������� ������ (����� ����������)
std::ostream& operator<<(std::ostream& os, const Polynomial& p) {
    for (int i = p.degree_; i >= 0; --i) {  // ������ � degree_
        // ���� ����������� ����� 0, ��� �������� �� �����
        if (p.coefficients_[i] == 0) continue;

        // ��� ������� �������� �� ����� ��������� "+" ��� "-"
        if (i == p.degree_) {
            os << p.coefficients_[i];
        }
        else {
            // ��� ��������� ��������� ��������� "+" ��� "-" � ����������� �� ����� ������������
            if (p.coefficients_[i] > 0) {
                os << " + " << p.coefficients_[i];
            }
            else {
                os << " - " << -p.coefficients_[i];
            }
        }

        // ����� �������, ���� ��� ������ 0
        if (i > 0) {
            os << "x^" << i;
        }
    }

    // ���� ������� ���������� (0 �������), ������� ������ ��� �����������
    if (p.degree_ == 0 && p.coefficients_[0] == 0) {
        os << 0;
    }

    return os;
}

void Polynomial::saveToTextFile(std::ofstream& file) const {
    if (!file.is_open()) {
        throw std::runtime_error("�� ������� ������� ���� ��� ������.");
    }
    // ������ �������
    file << degree_ << '\n';  // ������ � degree_
    // ������ �������������
    for (int i = 0; i < length_; ++i) {
        file << coefficients_[i] << (i < length_ - 1 ? " " : "\n");
    }
}

void Polynomial::loadFromTextFile(std::ifstream& file) {
    if (!file.is_open()) {
        throw std::runtime_error("�� ������� ������� ���� ��� ������.");
    }
    // ������ �������
    file >> degree_;
    length_ = degree_ + 1;

    // ������� ������ ������������
    delete[] coefficients_;
    coefficients_ = new double[length_];

    // ������ �������������
    for (int i = 0; i < length_; ++i) {
        file >> coefficients_[i];
    }
}

void Polynomial::saveToBinaryFile(std::ofstream& file) const {
    // ������ �������
    file.write(reinterpret_cast<const char*>(&degree_), sizeof(degree_));  // ������ � degree_

    // ������ �������������
    file.write(reinterpret_cast<const char*>(coefficients_), sizeof(double) * length_);
}

void Polynomial::loadFromBinaryFile(std::ifstream& file) {
    if (!file.is_open()) {
        throw std::runtime_error("�� ������� ������� ���� ��� ������.");
    }

    // ������ �������
    file.read(reinterpret_cast<char*>(&degree_), sizeof(degree_));
    length_ = degree_ + 1;

    // ������� ������ ������������
    delete[] coefficients_;
    coefficients_ = new double[length_];

    // ������ �������������
    file.read(reinterpret_cast<char*>(coefficients_), sizeof(double) * length_);
}


char* Polynomial::toString() const {
    static char result[512]; // ����������� ������ ��� �������� ����������
    result[0] = '\0';         // �������������� ������ ������

    for (int i = degree_; i >= 0; --i) {
        if (coefficients_[i] == 0.0) continue; // ���������� ������� ������������

        char buffer[50]; // ��������� ����� ��� �������� �����

        if (result[0] != '\0') { // ���� ��� �� ������ ����, ��������� "+" ��� "-"
            strcat(result, (coefficients_[i] > 0 ? "+" : "-"));
        }
        else if (coefficients_[i] < 0) { // ���� ������ ���� �������������
            strcat(result, "-");
        }

        // ��������� ������ ������������
        snprintf(buffer, sizeof(buffer), "%.0f", std::abs(coefficients_[i]));
        strcat(result, buffer);

        if (i > 0) strcat(result, "x"); // ��������� "x" ��� ���� �������� ������ 0
        if (i > 1) { // ��������� "^�������" ��� �������� ������ 1
            snprintf(buffer, sizeof(buffer), "^%d", i);
            strcat(result, buffer);
        }
    }

    return result[0] == '\0' ? (char*)"0" : result; // ���� ������ �����, ���������� "0"
}







