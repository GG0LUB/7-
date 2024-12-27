#ifndef NODE_H
#define NODE_H

#include <memory>
#include "Polynomial.h"

class Node {
public:
    std::unique_ptr<Polynomial> data; // Умный указатель для управления памятью
    Node* next;
    Node* prev;

    Node(Polynomial* data);
    ~Node();
};

#endif // NODE_H
