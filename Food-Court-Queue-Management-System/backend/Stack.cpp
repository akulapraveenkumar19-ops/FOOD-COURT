#include "Stack.h"
#include <iostream>

OrderStack::OrderStack() : topNode(nullptr), count(0) {}

OrderStack::~OrderStack() {
    clear();
}

void OrderStack::clear() {
    while (topNode != nullptr) {
        StackNode* temp = topNode;
        topNode = topNode->next;
        delete temp;
    }
    count = 0;
}

bool OrderStack::isEmpty() const {
    return topNode == nullptr;
}

int OrderStack::getSize() const {
    return count;
}

void OrderStack::push(const Order& order) {
    StackNode* newNode = new StackNode(order);
    newNode->next = topNode;
    topNode = newNode;
    count++;
}

bool OrderStack::pop(Order& order) {
    if (isEmpty()) {
        return false;
    }
    StackNode* temp = topNode;
    order = temp->data;
    topNode = topNode->next;
    delete temp;
    count--;
    return true;
}

bool OrderStack::top(Order& order) const {
    if (isEmpty()) {
        return false;
    }
    order = topNode->data;
    return true;
}

void OrderStack::display() const {
    if (isEmpty()) {
        std::cout << "[INFO] Order Stack is empty.\n";
        return;
    }

    std::cout << "\n========== RECENT ORDERS STACK (" << count << " Orders) ==========\n";
    std::cout << std::left
              << std::setw(10) << "Order ID"
              << std::setw(10) << "Token"
              << std::setw(16) << "Customer"
              << std::setw(25) << "Items"
              << std::setw(10) << "Total"
              << std::setw(12) << "Status"
              << "\n";
    std::cout << std::string(83, '-') << "\n";

    StackNode* curr = topNode;
    while (curr != nullptr) {
        curr->data.displaySummary();
        curr = curr->next;
    }
    std::cout << "========================================================\n\n";
}

void OrderStack::displayVisual() const {
    std::cout << "\n========================================\n";
    std::cout << "          ORDER STACK VISUALIZER        \n";
    std::cout << "========================================\n\n";

    if (isEmpty()) {
        std::cout << " Stack is EMPTY: [ TOP = NULL ]\n";
        std::cout << "========================================\n\n";
        return;
    }

    std::cout << " TOP\n";
    std::cout << "  |\n";
    std::cout << "  v\n";

    StackNode* curr = topNode;
    int limit = 0;
    while (curr != nullptr && limit < 10) {
        std::cout << "+--------------------------------------+\n";
        std::cout << "| " << std::left << std::setw(10) << curr->data.getOrderId()
                  << " " << std::setw(7) << curr->data.getTokenFormatted()
                  << " " << std::setw(12) << curr->data.getCustomerName().substr(0, 10)
                  << " Rs." << std::setw(4) << (int)curr->data.getTotalAmount() << " |\n";
        curr = curr->next;
        limit++;
    }
    std::cout << "+--------------------------------------+\n";
    std::cout << "               BOTTOM                  \n";
    std::cout << "========================================\n\n";
}
