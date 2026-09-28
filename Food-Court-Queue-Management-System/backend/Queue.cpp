#include "Queue.h"
#include <iostream>
#include <iomanip>

Queue::Queue(int capacity) : front(nullptr), rear(nullptr), count(0), maxCapacity(capacity) {}

Queue::~Queue() {
    clear();
}

void Queue::clear() {
    while (front != nullptr) {
        QueueNode* temp = front;
        front = front->next;
        delete temp;
    }
    rear = nullptr;
    count = 0;
}

bool Queue::isEmpty() const {
    return front == nullptr;
}

bool Queue::isFull() const {
    return count >= maxCapacity;
}

int Queue::getSize() const {
    return count;
}

bool Queue::enqueue(const Customer& customer) {
    if (isFull()) {
        std::cout << "[ERROR] Queue is FULL! Cannot accept more waiting customers.\n";
        return false;
    }

    QueueNode* newNode = new QueueNode(customer);
    if (rear == nullptr) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
    count++;
    return true;
}

bool Queue::dequeue(Customer& customer) {
    if (isEmpty()) {
        return false;
    }

    QueueNode* temp = front;
    customer = temp->data;
    front = front->next;

    if (front == nullptr) {
        rear = nullptr;
    }

    delete temp;
    count--;
    return true;
}

bool Queue::peek(Customer& customer) const {
    if (isEmpty()) {
        return false;
    }
    customer = front->data;
    return true;
}

void Queue::display() const {
    if (isEmpty()) {
        std::cout << "[INFO] Queue is currently empty. No waiting customers.\n";
        return;
    }

    std::cout << "\n========== CURRENT WAITING QUEUE (" << count << " Customers) ==========\n";
    Customer::printHeader();
    QueueNode* curr = front;
    while (curr != nullptr) {
        curr->data.displayRow();
        curr = curr->next;
    }
    std::cout << "========================================================\n\n";
}

void Queue::displayVisual() const {
    std::cout << "\n========================================\n";
    std::cout << "         NORMAL QUEUE VISUALIZER        \n";
    std::cout << "========================================\n\n";

    if (isEmpty()) {
        std::cout << " Queue is EMPTY: [ FRONT = NULL | REAR = NULL ]\n";
        std::cout << "========================================\n";
        return;
    }

    std::cout << " FRONT\n";
    std::cout << "   |\n";
    std::cout << "   v\n";

    QueueNode* curr = front;
    std::string arrowLine = "";
    int nodeCount = 0;

    while (curr != nullptr) {
        std::cout << "[" << curr->data.getTokenFormatted() << " : " 
                  << curr->data.getName().substr(0, 8) << "]";
        if (curr->next != nullptr) {
            std::cout << " ---> ";
        }
        curr = curr->next;
        nodeCount++;
    }
    std::cout << "\n";

    // Rear pointer indication
    std::cout << std::string((nodeCount > 0 ? (nodeCount - 1) * 16 : 0), ' ') << "   ^\n";
    std::cout << std::string((nodeCount > 0 ? (nodeCount - 1) * 16 : 0), ' ') << "   |\n";
    std::cout << std::string((nodeCount > 0 ? (nodeCount - 1) * 16 : 0), ' ') << "  REAR\n";
    std::cout << "========================================\n\n";
}

Customer* Queue::searchById(int id) {
    QueueNode* curr = front;
    while (curr != nullptr) {
        if (curr->data.getId() == id) {
            return &(curr->data);
        }
        curr = curr->next;
    }
    return nullptr;
}

Customer* Queue::searchByToken(int token) {
    QueueNode* curr = front;
    while (curr != nullptr) {
        if (curr->data.getToken() == token) {
            return &(curr->data);
        }
        curr = curr->next;
    }
    return nullptr;
}

Customer* Queue::searchByName(const std::string& name) {
    QueueNode* curr = front;
    while (curr != nullptr) {
        if (curr->data.getName() == name) {
            return &(curr->data);
        }
        curr = curr->next;
    }
    return nullptr;
}

Customer* Queue::searchByOrderId(const std::string& orderId) {
    QueueNode* curr = front;
    while (curr != nullptr) {
        if (curr->data.getOrderId() == orderId) {
            return &(curr->data);
        }
        curr = curr->next;
    }
    return nullptr;
}
