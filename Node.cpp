#include "node.h"
#include <iostream>

// Конструктор
Node::Node(Polynomial* data)
    : data(data ? std::make_unique<Polynomial>(*data) : nullptr), // Создаём копию объекта, если указатель не nullptr
    next(nullptr),
    prev(nullptr) {
    std::cout << "Node created with data address: "
        << (this->data ? this->data.get() : nullptr) << "\n";
}

// Деструктор
Node::~Node() {
    if (data) {
        std::cout << "Node destroyed with data address: " << data.get() << "\n";
    }
    else {
        std::cout << "Node destroyed with nullptr data\n";
    }
}
