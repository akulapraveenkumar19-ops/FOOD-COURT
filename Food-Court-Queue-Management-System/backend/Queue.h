#ifndef QUEUE_H
#define QUEUE_H

#include "Customer.h"

// Node structure for Queue linked list implementation
struct QueueNode {
    Customer data;
    QueueNode* next;

    QueueNode(const Customer& c) : data(c), next(nullptr) {}
};

class Queue {
private:
    QueueNode* front;
    QueueNode* rear;
    int count;
    int maxCapacity; // Can be set for bounded behavior or left unbounded

public:
    Queue(int capacity = 100);
    ~Queue();

    // Core Queue Operations
    bool enqueue(const Customer& customer);
    bool dequeue(Customer& customer);
    bool peek(Customer& customer) const;
    bool isEmpty() const;
    bool isFull() const;
    int getSize() const;
    void clear();

    // Display & Search
    void display() const;
    void displayVisual() const;
    Customer* searchById(int id);
    Customer* searchByToken(int token);
    Customer* searchByName(const std::string& name);
    Customer* searchByOrderId(const std::string& orderId);
};

#endif // QUEUE_H
