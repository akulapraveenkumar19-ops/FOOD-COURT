#include "PriorityQueue.h"
#include <iostream>
#include <vector>

PriorityQueue::PriorityQueue() : head(nullptr), count(0) {}

PriorityQueue::~PriorityQueue() {
    clear();
}

void PriorityQueue::clear() {
    while (head != nullptr) {
        PQNode* temp = head;
        head = head->next;
        delete temp;
    }
    count = 0;
}

bool PriorityQueue::isEmpty() const {
    return head == nullptr;
}

int PriorityQueue::getSize() const {
    return count;
}

void PriorityQueue::enqueue(const Customer& customer) {
    PQNode* newNode = new PQNode(customer);

    // If queue is empty or new customer has higher priority than head
    if (head == nullptr || newNode->priority > head->priority) {
        newNode->next = head;
        head = newNode;
    } else {
        // Find position: insert after all nodes with priority >= newNode->priority
        // This ensures FIFO order among elements with the same priority
        PQNode* curr = head;
        while (curr->next != nullptr && curr->next->priority >= newNode->priority) {
            curr = curr->next;
        }
        newNode->next = curr->next;
        curr->next = newNode;
    }
    count++;
}

bool PriorityQueue::dequeue(Customer& customer) {
    if (isEmpty()) {
        return false;
    }

    PQNode* temp = head;
    customer = temp->data;
    head = head->next;
    delete temp;
    count--;
    return true;
}

bool PriorityQueue::peek(Customer& customer) const {
    if (isEmpty()) {
        return false;
    }
    customer = head->data;
    return true;
}

void PriorityQueue::display() const {
    if (isEmpty()) {
        std::cout << "[INFO] Priority Queue is empty.\n";
        return;
    }

    std::cout << "\n========== PRIORITY QUEUE ORDERS (" << count << " Orders) ==========\n";
    Customer::printHeader();
    PQNode* curr = head;
    while (curr != nullptr) {
        curr->data.displayRow();
        curr = curr->next;
    }
    std::cout << "========================================================\n\n";
}

void PriorityQueue::displayVisual() const {
    std::cout << "\n========================================\n";
    std::cout << "       PRIORITY QUEUE VISUALIZER        \n";
    std::cout << "========================================\n\n";

    if (isEmpty()) {
        std::cout << " Priority Queue is EMPTY.\n";
        std::cout << "========================================\n\n";
        return;
    }

    std::vector<std::string> highList;
    std::vector<std::string> medList;
    std::vector<std::string> lowList;

    PQNode* curr = head;
    while (curr != nullptr) {
        std::string label = "[" + curr->data.getTokenFormatted() + " : " + curr->data.getName().substr(0, 8) + "]";
        if (curr->priority == 3) {
            highList.push_back(label);
        } else if (curr->priority == 2) {
            medList.push_back(label);
        } else {
            lowList.push_back(label);
        }
        curr = curr->next;
    }

    std::cout << " HIGH (Express - Served First)\n";
    std::cout << "  |\n";
    std::cout << "  v\n ";
    if (highList.empty()) {
        std::cout << " (None)\n";
    } else {
        for (size_t i = 0; i < highList.size(); ++i) {
            std::cout << highList[i];
            if (i + 1 < highList.size()) std::cout << " ---> ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    std::cout << " MEDIUM (Regular)\n";
    std::cout << "  |\n";
    std::cout << "  v\n ";
    if (medList.empty()) {
        std::cout << " (None)\n";
    } else {
        for (size_t i = 0; i < medList.size(); ++i) {
            std::cout << medList[i];
            if (i + 1 < medList.size()) std::cout << " ---> ";
        }
        std::cout << "\n";
    }
    std::cout << "\n";

    std::cout << " LOW (Normal)\n";
    std::cout << "  |\n";
    std::cout << "  v\n ";
    if (lowList.empty()) {
        std::cout << " (None)\n";
    } else {
        for (size_t i = 0; i < lowList.size(); ++i) {
            std::cout << lowList[i];
            if (i + 1 < lowList.size()) std::cout << " ---> ";
        }
        std::cout << "\n";
    }
    std::cout << "\n========================================\n\n";
}

Customer* PriorityQueue::searchById(int id) {
    PQNode* curr = head;
    while (curr != nullptr) {
        if (curr->data.getId() == id) {
            return &(curr->data);
        }
        curr = curr->next;
    }
    return nullptr;
}

Customer* PriorityQueue::searchByToken(int token) {
    PQNode* curr = head;
    while (curr != nullptr) {
        if (curr->data.getToken() == token) {
            return &(curr->data);
        }
        curr = curr->next;
    }
    return nullptr;
}
