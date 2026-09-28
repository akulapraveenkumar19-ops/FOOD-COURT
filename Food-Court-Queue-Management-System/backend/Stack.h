#ifndef STACK_H
#define STACK_H

#include "Order.h"

// Node structure for Stack of recent orders
struct StackNode {
    Order data;
    StackNode* next;

    StackNode(const Order& o) : data(o), next(nullptr) {}
};

class OrderStack {
private:
    StackNode* topNode;
    int count;

public:
    OrderStack();
    ~OrderStack();

    bool isEmpty() const;
    int getSize() const;
    void clear();

    // Stack Operations
    void push(const Order& order);
    bool pop(Order& order);
    bool top(Order& order) const;

    // Display & Visualizer
    void display() const;
    void displayVisual() const;
};

#endif // STACK_H
