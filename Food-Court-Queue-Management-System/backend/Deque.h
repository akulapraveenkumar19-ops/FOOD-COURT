#ifndef DEQUE_H
#define DEQUE_H

#include "Customer.h"

// Doubly Linked List Node for Deque
struct DequeNode {
    Customer data;
    DequeNode* prev;
    DequeNode* next;

    DequeNode(const Customer& c) : data(c), prev(nullptr), next(nullptr) {}
};

class Deque {
private:
    DequeNode* front;
    DequeNode* rear;
    int count;

public:
    Deque();
    ~Deque();

    bool isEmpty() const;
    int getSize() const;
    void clear();

    // Deque Operations
    void insertFront(const Customer& customer);
    void insertRear(const Customer& customer);
    bool deleteFront(Customer& customer);
    bool deleteRear(Customer& customer);
    bool getFront(Customer& customer) const;
    bool getRear(Customer& customer) const;

    // Display & Visualizer
    void display() const;
    void displayVisual() const;
};

#endif // DEQUE_H
