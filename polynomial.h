#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <fstream>
#include <iostream>
#include <vector>  
#include <stdexcept>  // ��� ���������� (��������, std::runtime_error)

using namespace std;

class Polynomial {
public:
    Polynomial();  // ����������� �� ���������
    Polynomial(int degree, const double* coeffs);  // ����������� � �����������
    Polynomial(const Polynomial& other);  // ����������� �����������
    Polynomial(Polynomial&& other) noexcept;            // ����������� �����������
    Polynomial& operator=(Polynomial&& other) noexcept; // �������� �����������

    virtual ~Polynomial();  // ����������

    virtual int getDegree() const;  // ���������� ������� ����������
    virtual double evaluate(double x) const;  // ���������� �������� ���������� ��� x
    virtual char* toString() const; // ����� toString
    static int getCount();  // ���������� ���������� ��������

    // ���������� ����������
    Polynomial operator-(const Polynomial& other) const;
    Polynomial& operator++();  // ���������� ���������
    Polynomial operator++(int);  // ����������� ���������
    Polynomial& operator--();  // ���������� ���������
    Polynomial operator--(int);  // ����������� ���������
    double operator()(double x) const;  // �������� ������ �������
    double& operator[](int index);  // �������� ��������������
    Polynomial& operator=(const Polynomial& other);  // �������� ������������

    // ���������� ��������� �����
    friend std::istream& operator>>(std::istream& is, Polynomial& p);

    // ���������� ��������� ������
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);

    void saveToTextFile(std::ofstream& file) const;  // ���������� � ��������� ����
    void loadFromTextFile(std::ifstream& file);     // �������� �� ���������� �����

    void saveToBinaryFile(std::ofstream& file) const; // ������ ������� � �������� ����
    void loadFromBinaryFile(std::ifstream& file);  // �������� ������� �� ��������� �����


protected:
    int degree_;  // ������ ��� ���������� ����
    double* coefficients_;
    int length_;
    static int count_;
    mutable char stringBuffer[1024];  // ����� ��� ������ toString
};

#endif // POLYNOMIAL_H
