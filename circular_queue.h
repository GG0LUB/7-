#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include "node.h"
#include <iostream>
#include <cstring>

class CircularQueue {
public:
    CircularQueue();
    ~CircularQueue();

    void add(Polynomial* data);         // Добавление объекта в конец очереди
    Polynomial* remove(); // Метод remove должен возвращать указатель на Polynomial
    void insertAt(int position, Polynomial* data); // Вставка по номеру
    void removeAt(int position);       // Удаление по номеру
    Polynomial* search(int degree);    // Поиск объекта по степени
    char* display() const;              // Просмотр всей структуры
    void print();

    // Для предоставления доступа тестам
    friend void testCircularQueue();

    int getSize() const;   // Возвращает размер очереди
    Node* getHead() const; // Возвращает указатель на голову очереди

private:
    Node* head; // Указатель на голову списка
    int size;   // Текущий размер очереди
};

#endif // CIRCULAR_QUEUE_H