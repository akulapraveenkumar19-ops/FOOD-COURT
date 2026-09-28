#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "Customer.h"

// Node structure for Priority Queue
struct PQNode {
    Customer data;
    int priority; // 3 = High, 2 = Medium, 1 = Low
    PQNode* next;

    PQNode(const Customer& c) : data(c), priority(c.getPriority()), next(nullptr) {}
};

class PriorityQueue {
private:
    PQNode* head;
    int count;

public:
    PriorityQueue();
    ~PriorityQueue();

    bool isEmpty() const;
    int getSize() const;
    void clear();

    // Priority Queue Operations
    void enqueue(const Customer& customer);
    bool dequeue(Customer& customer);
    bool peek(Customer& customer) const;

    // Display & Visualization
    void display() const;
    void displayVisual() const;

    // Search
    Customer* searchById(int id);
    Customer* searchByToken(int token);
};

#endif // PRIORITY_QUEUE_H
