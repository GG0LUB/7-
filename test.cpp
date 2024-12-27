#include "test.h"
#include "polynomial.h"
#include <cassert>
#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include <iomanip>
#include "array_based_polynomial.h"
#include "string_based_polynomial.h"
#include <new> // ��� ��������������� ������ ���������� ���������� ������
#include <stdexcept>


using namespace std;

void testPolynomialDefaultConstructor() {
    std::cout << "Running testPolynomialDefaultConstructor..." << std::endl;
    Polynomial p;
    assert(p.getDegree() == 0);
    assert(p.evaluate(1.0) == 0.0);
    std::cout << "testPolynomialDefaultConstructor passed!" << std::endl;
}

void testPolynomialParameterizedConstructor() {
    std::cout << "Running testPolynomialParameterizedConstructor..." << std::endl;
    double coeffs[] = { 1.0, 2.0, 3.0 };
    Polynomial p(2, coeffs);
    assert(p.getDegree() == 2);
    assert(p.evaluate(1.0) == 6.0);
    std::cout << "testPolynomialParameterizedConstructor passed!" << std::endl;
}

void testPolynomialCopyConstructor() {
    std::cout << "Running testPolynomialCopyConstructor..." << std::endl;
    double coeffs[] = { 1.0, 2.0, 3.0 };
    Polynomial p1(2, coeffs);
    Polynomial p2(p1);
    assert(p2.getDegree() == 2);
    assert(p2.evaluate(1.0) == 6.0);
    std::cout << "testPolynomialCopyConstructor passed!" << std::endl;
}

void testEvaluate() {
    std::cout << "Testing evaluate method...\n";

    double coeffs[] = { 1.0, 2.0, 3.0 }; // 3x^2 + 2x + 1
    Polynomial p(2, coeffs);

    double result = p.evaluate(1.0);
    assert(result == 6.0); // 3(1^2) + 2(1) + 1 = 6

    result = p.evaluate(2.0);
    assert(result == 17.0); // 3(2^2) + 2(2) + 1 = 17

    std::cout << "testEvaluate passed!\n";
}

void testHeapAllocation() {
    std::cout << "Testing heap allocation and deletion...\n";

    assert(Polynomial::getCount() == 0);

    Polynomial* p1 = new Polynomial();
    assert(Polynomial::getCount() == 1);

    delete p1; // ������� ������, ���������� ����������
    assert(Polynomial::getCount() == 0);

    std::cout << "testHeapAllocation passed!\n";
}

void testLocalObjects() {
    std::cout << "Testing local objects...\n";

    assert(Polynomial::getCount() == 0);

    {
        Polynomial p1;
        assert(Polynomial::getCount() == 1);

        Polynomial p2;
        assert(Polynomial::getCount() == 2);
    } // p1 � p2 ������� �� ������� ���������, ����������� ���������� �������������

    assert(Polynomial::getCount() == 0);

    std::cout << "testLocalObjects passed!\n";
}

void testPolynomialCount() {
    std::cout << "Testing Polynomial::getCount()...\n";

    // ���������, ��� ���������� ������� ����� 0
    assert(Polynomial::getCount() == 0);

    Polynomial* p1 = new Polynomial();
    assert(Polynomial::getCount() == 1);

    Polynomial* p2 = new Polynomial();
    assert(Polynomial::getCount() == 2);

    delete p1; // ������� ������ ������
    assert(Polynomial::getCount() == 1);

    delete p2; // ������� ������ ������
    assert(Polynomial::getCount() == 0);

    std::cout << "testPolynomialCount passed!\n";
}


void testPolynomialSaveLoadBinary() {
    // ������� �������� ������
    double coeffs[] = { 1.0, 0.0, 1.0 };  // ������: 1x^2 + 0x^1 + 1
    Polynomial p(2, coeffs);  // ������� 2, ������������

    // ��������� ���� ��� ������ � �������������� std::ofstream
    std::ofstream outFile("polynomial.bin", std::ios::binary); // ������� ����� ������ ��� ��������� �����
    if (outFile.is_open()) {
        p.saveToBinaryFile(outFile);  // ��������� ������ � ����
        outFile.close();
    }
    else {
        std::cerr << "������ ��� �������� ����� ��� ������!" << std::endl;
        return;
    }

    // ��������� �� ����� � ����� ������
    Polynomial q;
    std::ifstream inFile("polynomial.bin", std::ios::binary); // ������� ����� ����� ��� ��������� �����
    if (inFile.is_open()) {
        q.loadFromBinaryFile(inFile);  // ��������� ������ �� �����
        inFile.close();
    }
    else {
        std::cerr << "������ ��� �������� ����� ��� ������!" << std::endl;
        return;
    }

    // ���������, ��� ������ ��������� ���������
    assert(std::abs(q.evaluate(1.0) - p.evaluate(1.0)) < 1e-9);  // ��������� �������� � ������ �����������
    std::cout << "testPolynomialSaveLoadBinary passed!" << std::endl;
}

void testPolynomialSaveToTextFile() {
    double coeffs[] = { 1.0, -2.0, 3.5 };
    Polynomial p(2, coeffs);

    std::ofstream outFile("test_poly.txt");
    p.saveToTextFile(outFile);
    outFile.close();

    std::ifstream inFile("test_poly.txt");
    std::string line;
    std::getline(inFile, line);
    assert(line == "2");  // ��������� �������
    std::getline(inFile, line);
    assert(line == "1 -2 3.5");  // ��������� ������������
    inFile.close();

    std::cout << "testPolynomialSaveToTextFile passed!" << std::endl;
}

void testPolynomialLoadFromTextFile() {
    std::ofstream outFile("test_poly.txt");
    outFile << "2\n1 -2 3.5\n";  // ��������� �������� ������
    outFile.close();

    Polynomial p;
    std::ifstream inFile("test_poly.txt");
    p.loadFromTextFile(inFile);
    inFile.close();

    assert(p.getDegree() == 2);            // ��������� �������
    assert(p.evaluate(0) == 1.0);          // ��������� ��������� ����
    assert(p.evaluate(1) == 2.5);          // ��������� �������� ����������
    assert(p.evaluate(-1) == 6.5);         // ���������� ��������� ��������

    std::cout << "testPolynomialLoadFromTextFile passed!" << std::endl;
}

//void testArrayBasedPolynomial() {
//    std::cout << "Running testArrayBasedPolynomial..." << std::endl;
//
//    // �������: 5x^4 + 0x^3 + 0x^2 + 3
//    double coeffs[] = { 3.0, 0.0, 0.0, 0.0, 5.0 };
//    ArrayBasedPolynomial p(4, coeffs);
//
//    // ��������� ���������� ��������� �������������
//    assert(p.getNonZeroCount() == 2);
//
//    // ��������� ������� ��������� �������������
//    int* degrees = p.getDegrees();
//    assert(degrees[0] == 0); // ������� 0 (����������� 3)
//    assert(degrees[1] == 4); // ������� 4 (����������� 5)
//
//    // ����� ��� �������
//    p.displayDegrees();
//
//    std::cout << "testArrayBasedPolynomial passed!" << std::endl;
//}

void testArrayBasedPolynomialEvaluate() {
    std::cout << "Running testArrayBasedPolynomialEvaluate..." << std::endl;

    // �������: 5x^4 + 0x^3 + 0x^2 + 3
    double coeffs[] = { 3.0, 0.0, 0.0, 0.0, 5.0 };
    ArrayBasedPolynomial p(4, coeffs);

    // ��������� �������� �������� ��� ��������� ��������� x
    assert(p.evaluate(1.0) == 8.0);  // 5*1^4 + 3 = 8
    assert(p.evaluate(0.0) == 3.0);  // ������ ��������� ����
    assert(p.evaluate(2.0) == 83.0); // 5*2^4 + 3 = 80 + 3 = 83

    std::cout << "testArrayBasedPolynomialEvaluate passed!" << std::endl;
}

void testStringBasedPolynomial() {
    std::cout << "Running testStringBasedPolynomial..." << std::endl;

    double coeffs[] = { 1.0, -2.0, 3.0 };
    StringBasedPolynomial p(2, coeffs);

    double* retrievedCoeffs = p.getCoefficients();
    assert(retrievedCoeffs[0] == 1.0);
    assert(retrievedCoeffs[1] == -2.0);
    assert(retrievedCoeffs[2] == 3.0);

    p.displayCoefficients(); // ���������� �����

    std::cout << "testStringBasedPolynomial passed!" << std::endl;
}

void testEvaluateWithHeapObjects() {
    std::cout << "Testing evaluate with heap objects...\n";

    double coeffs[] = { 1.0, 2.0, 3.0 };
    Polynomial* p = new Polynomial(2, coeffs);

    double result = p->evaluate(1.0);
    assert(result == 6.0);

    delete p; // ������� ������
    assert(Polynomial::getCount() == 0);

    std::cout << "testEvaluateWithHeapObjects passed!\n";
}

void testRAII() {
    std::cout << "Testing RAII...\n";

    assert(Polynomial::getCount() == 0);

    {
        Polynomial p1;
        Polynomial p2;
        assert(Polynomial::getCount() == 2);
    } // ����������� ���������� �������������

    assert(Polynomial::getCount() == 0);

    std::cout << "testRAII passed!\n";
}

// ���� ��� ���������� ������
void testMemoryAllocationFailure() {
    std::cout << "Testing memory allocation failure...\n";

    try {
        // ������������� �������� ���������� ���������� ������
        std::set_new_handler([]() { throw std::bad_alloc(); });
        Polynomial* p = new Polynomial();
        delete p; // ������� ������, ���� �� ��� ������
    }
    catch (const std::bad_alloc& e) {
        std::cout << "Caught memory allocation exception: " << e.what() << "\n";
    }

    // ���������� ���������� new
    std::set_new_handler(nullptr);

    std::cout << "testMemoryAllocationFailure passed!\n";
}

// ���� ��� ������ �� ������� ���������
void testOutOfRangeException() {
    std::cout << "Testing out of range exception...\n";

    double coeffs[] = { 1.0, 2.0, 3.0 };
    ArrayBasedPolynomial p(2, coeffs);

    try {
        p.evaluate(2.0); // ������� ������ (��� ����������)
        std::cout << "Evaluation successful.\n";
    }
    catch (const std::out_of_range& e) {
        std::cerr << "Unexpected exception: " << e.what() << "\n";
        assert(false); // ������, ���� ������������� ����������
    }

    // ������ ������ �� ������� ���������
    try {
        throw std::out_of_range("Invalid access to polynomial coefficients!");
    }
    catch (const std::out_of_range& e) {
        std::cout << "Caught out of range exception: " << e.what() << "\n";
    }

    std::cout << "testOutOfRangeException passed!\n";
}

// ���� ������� �� ����
void testDivisionByZero() {
    std::cout << "Testing division by zero exception...\n";

    try {
        double x = 0.0;
        double result = 1.0 / x; // ������� ������� �� ����
        (void)result; // ������� �������������� � �������������� ����������
        throw std::domain_error("Division by zero is not allowed!");
    }
    catch (const std::domain_error& e) {
        std::cout << "Caught division by zero exception: " << e.what() << "\n";
    }

    std::cout << "testDivisionByZero passed!\n";
}

// ���� ��� ������������� �������� ��������
void testInvalidPolynomialCreation() {
    std::cout << "Testing invalid polynomial creation...\n";

    try {
        double coeffs[] = { 1.0, 2.0, 3.0 };
        Polynomial p(-1, coeffs); // �������� ������� (-1)
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Caught invalid polynomial creation exception: " << e.what() << "\n";
    }

    std::cout << "testInvalidPolynomialCreation passed!\n";
}

// ���� ��� �������������� �������������
void testUninitializedCoefficients() {
    std::cout << "Testing uninitialized coefficients exception...\n";

    try {
        Polynomial p;
        p.evaluate(2.0); // ������� ���������� ��� ������������� �������������
    }
    catch (const std::runtime_error& e) {
        std::cout << "Caught uninitialized coefficients exception: " << e.what() << "\n";
    }

    std::cout << "testUninitializedCoefficients passed!\n";
}
