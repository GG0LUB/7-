#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include "node.h"
#include <iostream>
#include <cstring>

class CircularQueue {
public:
    CircularQueue();
    ~CircularQueue();

    void add(Polynomial* data);         // ���������� ������� � ����� �������
    Polynomial* remove(); // ����� remove ������ ���������� ��������� �� Polynomial
    void insertAt(int position, Polynomial* data); // ������� �� ������
    void removeAt(int position);       // �������� �� ������
    Polynomial* search(int degree);    // ����� ������� �� �������
    char* display() const;              // �������� ���� ���������
    void print();

    // ��� �������������� ������� ������
    friend void testCircularQueue();

    int getSize() const;   // ���������� ������ �������
    Node* getHead() const; // ���������� ��������� �� ������ �������

private:
    Node* head; // ��������� �� ������ ������
    int size;   // ������� ������ �������
};

#endif // CIRCULAR_QUEUE_H