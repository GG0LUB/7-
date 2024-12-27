#ifndef POLYNOMIAL_H
#define POLYNOMIAL_H

#include <fstream>
#include <iostream>
#include <vector>  
#include <stdexcept>  // Для исключений (например, std::runtime_error)

using namespace std;

class Polynomial {
public:
    Polynomial();  // Конструктор по умолчанию
    Polynomial(int degree, const double* coeffs);  // Конструктор с параметрами
    Polynomial(const Polynomial& other);  // Конструктор копирования
    Polynomial(Polynomial&& other) noexcept;            // Конструктор перемещения
    Polynomial& operator=(Polynomial&& other) noexcept; // Оператор перемещения

    virtual ~Polynomial();  // Деструктор

    virtual int getDegree() const;  // Возвращает степень многочлена
    virtual double evaluate(double x) const;  // Вычисление значения многочлена для x
    virtual char* toString() const; // Метод toString
    static int getCount();  // Возвращает количество объектов

    // Перегрузка операторов
    Polynomial operator-(const Polynomial& other) const;
    Polynomial& operator++();  // Префиксный инкремент
    Polynomial operator++(int);  // Постфиксный инкремент
    Polynomial& operator--();  // Префиксный декремент
    Polynomial operator--(int);  // Постфиксный декремент
    double operator()(double x) const;  // Операция вызова функции
    double& operator[](int index);  // Операция индексирования
    Polynomial& operator=(const Polynomial& other);  // Операция присваивания

    // Перегрузка оператора ввода
    friend std::istream& operator>>(std::istream& is, Polynomial& p);

    // Перегрузка оператора вывода
    friend std::ostream& operator<<(std::ostream& os, const Polynomial& p);

    void saveToTextFile(std::ofstream& file) const;  // Сохранение в текстовый файл
    void loadFromTextFile(std::ifstream& file);     // Загрузка из текстового файла

    void saveToBinaryFile(std::ofstream& file) const; // Запись объекта в двоичный файл
    void loadFromBinaryFile(std::ifstream& file);  // Загрузка объекта из двоичного файла


protected:
    int degree_;  // Теперь это защищённый член
    double* coefficients_;
    int length_;
    static int count_;
    mutable char stringBuffer[1024];  // Буфер для метода toString
};

#endif // POLYNOMIAL_H
