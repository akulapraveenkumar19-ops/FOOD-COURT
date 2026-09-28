#include "Deque.h"
#include <iostream>

Deque::Deque() : front(nullptr), rear(nullptr), count(0) {}

Deque::~Deque() {
    clear();
}

void Deque::clear() {
    while (front != nullptr) {
        DequeNode* temp = front;
        front = front->next;
        delete temp;
    }
    rear = nullptr;
    count = 0;
}

bool Deque::isEmpty() const {
    return front == nullptr;
}

int Deque::getSize() const {
    return count;
}

void Deque::insertFront(const Customer& customer) {
    DequeNode* newNode = new DequeNode(customer);
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        newNode->next = front;
        front->prev = newNode;
        front = newNode;
    }
    count++;
}

void Deque::insertRear(const Customer& customer) {
    DequeNode* newNode = new DequeNode(customer);
    if (isEmpty()) {
        front = rear = newNode;
    } else {
        newNode->prev = rear;
        rear->next = newNode;
        rear = newNode;
    }
    count++;
}

bool Deque::deleteFront(Customer& customer) {
    if (isEmpty()) {
        return false;
    }

    DequeNode* temp = front;
    customer = temp->data;

    front = front->next;
    if (front != nullptr) {
        front->prev = nullptr;
    } else {
        rear = nullptr;
    }

    delete temp;
    count--;
    return true;
}

bool Deque::deleteRear(Customer& customer) {
    if (isEmpty()) {
        return false;
    }

    DequeNode* temp = rear;
    customer = temp->data;

    rear = rear->prev;
    if (rear != nullptr) {
        rear->next = nullptr;
    } else {
        front = nullptr;
    }

    delete temp;
    count--;
    return true;
}

bool Deque::getFront(Customer& customer) const {
    if (isEmpty()) {
        return false;
    }
    customer = front->data;
    return true;
}

bool Deque::getRear(Customer& customer) const {
    if (isEmpty()) {
        return false;
    }
    customer = rear->data;
    return true;
}

void Deque::display() const {
    if (isEmpty()) {
        std::cout << "[INFO] Deque is empty.\n";
        return;
    }

    std::cout << "\n========== DEQUE ORDERS (" << count << " Elements) ==========\n";
    Customer::printHeader();
    DequeNode* curr = front;
    while (curr != nullptr) {
        curr->data.displayRow();
        curr = curr->next;
    }
    std::cout << "========================================================\n\n";
}

void Deque::displayVisual() const {
    std::cout << "\n========================================\n";
    std::cout << "             DEQUE VISUALIZER           \n";
    std::cout << "========================================\n\n";

    if (isEmpty()) {
        std::cout << " Deque is EMPTY: [ FRONT = NULL | REAR = NULL ]\n";
        std::cout << "========================================\n\n";
        return;
    }

    std::cout << " FRONT\n";
    std::cout << "   |\n";
    std::cout << "   v\n";

    DequeNode* curr = front;
    int nodeCount = 0;
    while (curr != nullptr) {
        std::cout << "[" << curr->data.getTokenFormatted() << ":" << curr->data.getName().substr(0, 6) << "]";
        if (curr->next != nullptr) {
            std::cout << " <===> ";
        }
        curr = curr->next;
        nodeCount++;
    }
    std::cout << "\n";

    int offset = (nodeCount > 0 ? (nodeCount - 1) * 16 : 0);
    std::cout << std::string(offset, ' ') << "   ^\n";
    std::cout << std::string(offset, ' ') << "   |\n";
    std::cout << std::string(offset, ' ') << "  REAR\n";
    std::cout << "========================================\n\n";
}
