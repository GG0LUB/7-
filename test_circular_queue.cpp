#include "circular_queue.h"
#include "array_based_polynomial.h"
#include "string_based_polynomial.h"
#include "CircularQueueTempl.h"
#include <cassert>
#include <iostream>

#pragma warning (disable : 4996)

void normalizePolynomialString(const char* str, char* normalized) {
    int j = 0;
    for (int i = 0; str[i] != '\0'; ++i) {
        if (str[i] != ' ') { // ������� �������
            normalized[j++] = str[i];
        }
    }
    normalized[j] = '\0'; // ��������� ������ ������� ��������
}

// ���� ��� ArrayBasedPolynomial
void testArrayBasedPolynomialToString() {
    std::cout << "Testing ArrayBasedPolynomial toString()...\n";

    double coeffs[] = { 1.0, 2.0, 3.0 }; // �������: 3x^2 + 2x + 1
    ArrayBasedPolynomial p(2, coeffs);

    char result[256];
    strcpy(result, p.toString());

    std::cout << "Generated string: \"" << result << "\"\n";

    assert(strcmp(result, "3x^2+2x+1") == 0);
    std::cout << "testArrayBasedPolynomialToString passed!\n";
}





// ���� ��� StringBasedPolynomial
void testStringBasedPolynomialToString() {
    std::cout << "Testing StringBasedPolynomial toString()...\n";

    double coeffs[] = { 0.0, -4.0, 0.0, 5.0 }; // �������: 5x^3 - 4x
    StringBasedPolynomial p(3, coeffs);

    char result[256];
    strcpy(result, p.toString());

    std::cout << "Generated string: \"" << result << "\"\n";

    assert(strcmp(result, "5x^3-4x") == 0);
    std::cout << "testStringBasedPolynomialToString passed!\n";
}




// ���� ��� ������ � CircularQueue
void testCircularQueue() {
    CircularQueue queue;

    // ������� 1: 3x^2 + 2x + 1
    double coeffs1[] = { 1.0, 2.0, 3.0 };
    Polynomial* p1 = new ArrayBasedPolynomial(2, coeffs1);

    // ������� 2: 5x^3 - 4x
    double coeffs2[] = { 0.0, -4.0, 0.0, 5.0 };
    Polynomial* p2 = new StringBasedPolynomial(3, coeffs2);

    // ��������� �������� � �������
    queue.add(p1);
    queue.add(p2);

    // ��������� ������ �������
    const char* firstResult = queue.getHead()->data->toString();
    std::cout << "First polynomial in queue: \"" << firstResult << "\"\n";

    assert(strcmp(firstResult, "3x^2+2x+1") == 0);

    // ��������� ������ �������
    const char* secondResult = queue.getHead()->next->data->toString();
    std::cout << "Second polynomial in queue: \"" << secondResult << "\"\n";

    assert(strcmp(secondResult, "5x^3-4x") == 0);

    // ������ ������
    delete p1;
    delete p2;

    std::cout << "testCircularQueue passed!\n";
}




// ���� �� ���������� � �������� � CircularQueue
void testCircularQueueAddRemove() {
    std::cout << "Testing CircularQueue add and remove...\n";

    CircularQueue queue;

    // ������ �������: 2x^2 + 1
    double coeffs[] = { 1.0, 0.0, 2.0 }; // ������������ ��� �������� 2x^2 + 1
    queue.add(new ArrayBasedPolynomial(2, coeffs)); // ��������� ������� � �������

    // ������� �������
    Polynomial* removed = queue.remove(); // ������� ������ �������
    if (!removed) {
        std::cerr << "Error: No polynomial was removed!\n";
        assert(false);
    }

    // ��������� ��������� ������������� ��������� ��������
    char result[256];
    strcpy(result, removed->toString());
    std::cout << "Removed polynomial: " << result << "\n";

    assert(strcmp(result, "2x^2+1") == 0);

    // ������� ������ ��������, ����� �������� ������ ������
    delete removed;

    std::cout << "testCircularQueueAddRemove passed!\n";
}





void testCircularQueueOrder() {
    CircularQueue queue;

    // �������� ��� �����
    double coeffs1[] = { 1.0, 2.0, 3.0 }; // 3x^2 + 2x + 1
    double coeffs2[] = { 0.0, -1.0, 2.0, 3.0 }; // 3x^3 + 2x^2 - x
    double coeffs3[] = { 5.0, 6.0 }; // 6x + 5

    // ���������� ���������
    queue.add(new ArrayBasedPolynomial(2, coeffs1));
    queue.add(new ArrayBasedPolynomial(3, coeffs2));
    queue.add(new ArrayBasedPolynomial(1, coeffs3));

    // �������� ����������� �������
    std::cout << "Queue contents:\n";
    queue.print();

    // �������� ���������
    queue.remove();
    queue.remove();
    queue.remove();

    // �������� �������� �� ������ �������
    try {
        queue.remove();
    }
    catch (const std::runtime_error& e) {
        std::cerr << e.what() << "\n";
    }

    std::cout << "testCircularQueueOrder passed!\n";
}




void testCircularQueueExceptions() {
    std::cout << "Testing CircularQueue exception handling...\n";

    CircularQueue queue;

    // ����: �������� �� ������ �������
    try {
        std::cout << "Attempting to remove from an empty queue...\n";
        queue.remove(); // ���� ������� �����, ������ ���� ��������� ����������
        assert(false);  // ���� ���� ������, ���������� �� ���� ���������
    }
    catch (const std::runtime_error& e) {
        std::cout << "Caught expected exception: " << e.what() << "\n";
    }
    catch (...) {
        std::cerr << "Caught unexpected exception!\n";
        assert(false); // ���� ����������� ������ ����������, ���� ��������
    }

    std::cout << "testCircularQueueExceptions passed!\n";
}



void testPolynomialToString() {
    std::cout << "Testing Base Polynomial toString...\n";

    double coeffs[] = { 1.0, 2.0, 3.0 }; // �������: 3x^2 + 2x + 1
    Polynomial p(2, coeffs);

    char* result = p.toString();
    std::cout << "Generated string: \"" << result << "\"\n";

    char normalized[256];
    normalizePolynomialString(result, normalized);

    // ���������� ��������������� ������
    assert(strcmp(normalized, "3x^2+2x+1") == 0);
    std::cout << "testPolynomialToString passed!\n";
}

void testCircularQueueTempl() {
    // ���� � int
    CircularQueueTempl<int> intQueue;
    intQueue.add(1);
    intQueue.add(2);
    intQueue.add(3);
    intQueue.print();
    std::cout << "Removed: " << intQueue.remove() << "\n";
    intQueue.print();

    // ���� � float
    CircularQueueTempl<float> floatQueue;
    floatQueue.add(1.1f);
    floatQueue.add(2.2f);
    floatQueue.add(3.3f);
    floatQueue.print();
    std::cout << "Removed: " << floatQueue.remove() << "\n";
    floatQueue.print();

    // ���� � Polynomial
    CircularQueueTempl<Polynomial> polyQueue;
    double coeffs1[] = { 1.0, 0.0, 2.0 }; // 2x^2 + 1
    double coeffs2[] = { 0.0, -1.0, 3.0 }; // 3x^2 - x
    polyQueue.add(Polynomial(2, coeffs1));
    polyQueue.add(Polynomial(2, coeffs2));
    polyQueue.print();
    Polynomial removedPoly = polyQueue.remove();
    std::cout << "Removed polynomial: " << removedPoly.toString() << "\n";
    polyQueue.print();
    std::cout << "testCircularQueueTempl passed!\n";
}