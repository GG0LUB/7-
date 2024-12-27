#ifndef CIRCULAR_QUEUE_TEMPL_H
#define CIRCULAR_QUEUE_TEMPL_H

#include <iostream>
#include <stdexcept>
#include <memory>
#include "polynomial.h" 

// ���� ����������� ������
template <typename T>
struct NodeTempl {
    T data;
    NodeTempl* next;
    NodeTempl* prev;

    NodeTempl(const T& value) : data(value), next(nullptr), prev(nullptr) {}
};

// ��������� ����� CircularQueueTempl
template <typename T>
class CircularQueueTempl {
private:
    NodeTempl<T>* head;
    size_t count;

public:
    CircularQueueTempl() : head(nullptr), count(0) {}
    ~CircularQueueTempl();

    void add(const T& value);
    T remove();
    size_t size() const { return count; }
    bool isEmpty() const { return count == 0; }
    void print() const;

    // ��� ������������
    NodeTempl<T>* getHead() const { return head; }
};

// ���������� �����������
template <typename T>
CircularQueueTempl<T>::~CircularQueueTempl() {
    while (!isEmpty()) {
        remove();
    }
}

// ���������� ������ add
template <typename T>
void CircularQueueTempl<T>::add(const T& value) {
    NodeTempl<T>* newNode = new NodeTempl<T>(value);
    if (!head) {
        head = newNode;
        head->next = head;
        head->prev = head;
    }
    else {
        NodeTempl<T>* tail = head->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = head;
        head->prev = newNode;
    }
    ++count;
}

// ���������� ������ remove
template <typename T>
T CircularQueueTempl<T>::remove() {
    if (!head) {
        throw std::runtime_error("Queue is empty, cannot remove.");
    }

    NodeTempl<T>* toDelete = head;
    T value = toDelete->data;

    if (head->next == head) { // ���� � ������� ���� �������
        head = nullptr;
    }
    else {
        head->prev->next = head->next;
        head->next->prev = head->prev;
        head = head->next;
    }

    delete toDelete;
    --count;

    return value;
}

// ���������� ������ print
template <typename T>
void CircularQueueTempl<T>::print() const {
    if (!head) {
        std::cout << "Queue is empty.\n";
        return;
    }

    NodeTempl<T>* current = head;
    do {
        std::cout << current->data << " ";
        current = current->next;
    } while (current != head);

    std::cout << "\n";
}

#include "Polynomial.h"

// ������������� ��� Polynomial
template <>
class CircularQueueTempl<Polynomial> {
private:
    NodeTempl<Polynomial>* head;
    size_t count;

public:
    CircularQueueTempl() : head(nullptr), count(0) {}
    ~CircularQueueTempl();

    void add(const Polynomial& value);
    Polynomial remove();
    size_t size() const { return count; }
    bool isEmpty() const { return count == 0; }
    void print() const;

    NodeTempl<Polynomial>* getHead() const { return head; }
};

// ���������� �����������
CircularQueueTempl<Polynomial>::~CircularQueueTempl() {
    while (!isEmpty()) {
        remove();
    }
}

// ���������� ������ add
void CircularQueueTempl<Polynomial>::add(const Polynomial& value) {
    NodeTempl<Polynomial>* newNode = new NodeTempl<Polynomial>(value);
    if (!head) {
        head = newNode;
        head->next = head;
        head->prev = head;
    }
    else {
        NodeTempl<Polynomial>* tail = head->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = head;
        head->prev = newNode;
    }
    ++count;
}

// ���������� ������ remove
Polynomial CircularQueueTempl<Polynomial>::remove() {
    if (!head) {
        throw std::runtime_error("Queue is empty, cannot remove.");
    }

    NodeTempl<Polynomial>* toDelete = head;
    Polynomial value = toDelete->data;

    if (head->next == head) {
        head = nullptr;
    }
    else {
        head->prev->next = head->next;
        head->next->prev = head->prev;
        head = head->next;
    }

    delete toDelete;
    --count;

    return value;
}

// ���������� ������ print
void CircularQueueTempl<Polynomial>::print() const {
    if (!head) {
        std::cout << "Queue is empty.\n";
        return;
    }

    NodeTempl<Polynomial>* current = head;
    do {
        std::cout << current->data.toString() << " ";
        current = current->next;
    } while (current != head);

    std::cout << "\n";
}


#endif // CIRCULAR_QUEUE_TEMPL_H
