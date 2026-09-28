#include "CircularQueue.h"

CircularQueue::CircularQueue(int size)
    : front(-1), rear(-1), capacity(size), count(0) {
    queue = new int[capacity];
    for (int i = 0; i < capacity; i++) {
        queue[i] = 0;
    }
}

CircularQueue::~CircularQueue() {
    delete[] queue;
}

void CircularQueue::clear() {
    front = -1;
    rear = -1;
    count = 0;
    for (int i = 0; i < capacity; i++) {
        queue[i] = 0;
    }
}

bool CircularQueue::isFull() const {
    return count == capacity;
}

bool CircularQueue::isEmpty() const {
    return count == 0;
}

int CircularQueue::getSize() const {
    return count;
}

int CircularQueue::getCapacity() const {
    return capacity;
}

bool CircularQueue::addToken(int token) {
    if (isFull()) {
        std::cout << "[ERROR] Circular Queue is FULL! Max capacity of " << capacity << " reached.\n";
        return false;
    }

    if (isEmpty()) {
        front = rear = 0;
    } else {
        rear = (rear + 1) % capacity;
    }

    queue[rear] = token;
    count++;
    return true;
}

bool CircularQueue::serveToken(int& token) {
    if (isEmpty()) {
        std::cout << "[INFO] Circular Queue is EMPTY. No tokens to serve.\n";
        return false;
    }

    token = queue[front];
    queue[front] = 0; // Reset slot

    if (front == rear) {
        front = rear = -1;
    } else {
        front = (front + 1) % capacity;
    }

    count--;
    return true;
}

int CircularQueue::peek() const {
    if (isEmpty()) {
        return -1;
    }
    return queue[front];
}

void CircularQueue::display() const {
    if (isEmpty()) {
        std::cout << "[INFO] Circular Queue: No active tokens.\n";
        return;
    }

    std::cout << "\n========== ACTIVE TOKENS IN CIRCULAR QUEUE (" << count << "/" << capacity << ") ==========\n";
    std::cout << "Front index: " << front << " | Rear index: " << rear << "\n";
    std::cout << "Tokens: ";
    int idx = front;
    for (int i = 0; i < count; i++) {
        std::cout << "T-" << std::setw(3) << std::setfill('0') << queue[idx];
        if (i < count - 1) std::cout << " -> ";
        idx = (idx + 1) % capacity;
    }
    std::cout << "\n============================================================\n\n";
}

void CircularQueue::displayVisual() const {
    std::cout << "\n===================================================\n";
    std::cout << "           CIRCULAR QUEUE BUFFER SLOTS             \n";
    std::cout << "===================================================\n";
    std::cout << "Slot Index: ";
    for (int i = 0; i < capacity; i++) {
        std::cout << "[" << std::setw(2) << i << "] ";
    }
    std::cout << "\nToken Val : ";
    for (int i = 0; i < capacity; i++) {
        if (queue[i] != 0) {
            std::cout << " T" << std::setw(2) << queue[i] << " ";
        } else {
            std::cout << "  --  ";
        }
    }
    std::cout << "\nPointers  : ";
    for (int i = 0; i < capacity; i++) {
        std::string ptr = "";
        if (i == front && i == rear && !isEmpty()) ptr = "F&R";
        else if (i == front && !isEmpty()) ptr = "FRNT";
        else if (i == rear && !isEmpty()) ptr = "REAR";
        else ptr = "    ";
        std::cout << std::setw(5) << ptr << " ";
    }
    std::cout << "\n";
    std::cout << "Status: " << (isFull() ? "FULL" : (isEmpty() ? "EMPTY" : "ACTIVE"))
              << " | Total: " << count << " / " << capacity << "\n";
    std::cout << "===================================================\n\n";
}

std::vector<int> CircularQueue::getActiveTokens() const {
    std::vector<int> active;
    if (isEmpty()) return active;
    int idx = front;
    for (int i = 0; i < count; i++) {
        active.push_back(queue[idx]);
        idx = (idx + 1) % capacity;
    }
    return active;
}
