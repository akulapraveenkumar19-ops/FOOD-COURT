#ifndef CIRCULAR_QUEUE_H
#define CIRCULAR_QUEUE_H

#include <iostream>
#include <iomanip>
#include <vector>
#include <string>

class CircularQueue {
private:
    int* queue;
    int front;
    int rear;
    int capacity;
    int count;

public:
    CircularQueue(int size = 10);
    ~CircularQueue();

    bool isFull() const;
    bool isEmpty() const;
    int getSize() const;
    int getCapacity() const;

    bool addToken(int token);
    bool serveToken(int& token);
    int peek() const;

    void display() const;
    void displayVisual() const;
    std::vector<int> getActiveTokens() const;
    void clear();
};

#endif // CIRCULAR_QUEUE_H
