#include "circular_queue.h"
#include <stdexcept>
#include <sstream>

CircularQueue::CircularQueue() : head(nullptr), size(0) {}

CircularQueue::~CircularQueue() {
    while (size > 0) {
        remove(); // Удаляем все узлы
    }
}

void CircularQueue::add(Polynomial* poly) {
    if (!poly) {
        throw std::invalid_argument("Cannot add nullptr polynomial to the queue");
    }

    Node* newNode = new Node(poly);
    if (!head) {
        head = newNode;
        head->next = head;
        head->prev = head;
    }
    else {
        Node* tail = head->prev;
        tail->next = newNode;
        newNode->prev = tail;
        newNode->next = head;
        head->prev = newNode;
    }
    char* buffer= poly->toString();
    std::cout << "Added polynomial: " << buffer << "\n";
}

Polynomial* CircularQueue::remove() {
    if (!head) {
        throw std::runtime_error("Queue is empty, cannot remove.");
    }

    Node* toDelete = head;
    std::unique_ptr<Polynomial> data = std::move(toDelete->data); // Передаём владение объектом

    if (head->next == head) { // Если в очереди один элемент
        head = nullptr;
    }
    else {
        head->prev->next = head->next;
        head->next->prev = head->prev;
        head = head->next;
    }

    delete toDelete; // Удаляем узел

    return data.release(); // Освобождаем владение и возвращаем "сырой" указатель
}

void CircularQueue::insertAt(int position, Polynomial* data) {
    if (position < 0 || position > size) {
        throw std::out_of_range("Position is out of range.");
    }
    Node* newNode = new Node(data);
    if (!head) {
        head = newNode;
        head->next = head;
        head->prev = head;
    }
    else {
        Node* current = head;
        for (int i = 0; i < position; ++i) {
            current = current->next;
        }
        newNode->next = current->next;
        newNode->prev = current;
        current->next->prev = newNode;
        current->next = newNode;
    }
    ++size;
}

void CircularQueue::removeAt(int position) {
    if (position < 0 || position >= size) {
        std::cout << "Invalid position.\n";
        return;
    }
    if (position == 0) {
        remove();
        return;
    }
    Node* current = head;
    for (int i = 0; i < position; ++i) {
        current = current->next;
    }
    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
    --size;
}

Polynomial* CircularQueue::search(int degree) {
    if (!head) {
        return nullptr;
    }
    Node* current = head;
    do {
        if (current->data->getDegree() == degree) {
            return current->data.get(); // Возвращаем "сырой" указатель через get()
        }
        current = current->next;
    } while (current != head);
    return nullptr;
}

char* CircularQueue::display() const {
    if (!head) {
        std::cout << "Queue is empty.\n";
        return NULL;
    }

    Node* current = head;
    std::stringstream ss;

    do {
        const char* result = current->data->toString();
        ss << result << "\n"; // Добавляем строку представления полинома в stringstream
        current = current->next;
    } while (current != head);

    char* result = new char[ss.str().length() + 1];
    strcpy(result, ss.str().c_str());
    return result;
}

int CircularQueue::getSize() const {
    return size;
}

Node* CircularQueue::getHead() const {
    return head;
}

void CircularQueue::print() {
    if (!head) {
        std::cout << "Queue is empty.\n";
        return;
    }

    Node* current = head;
    std::stringstream ss;

    do {
        if (current->data) {
            const char* result = current->data->toString();
            ss << result << " ";
        }
        else {
            ss << "nullptr ";
        }
        current = current->next;
    } while (current != head);

    std::cout << ss.str() << "\n"; // Выводим содержимое stringstream
}