#ifndef MYSTACK_H
#define MYSTACK_H

#include "AbstractStack.h"
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class myStack : public AbstractStack<T> {
private:
    T* arr;
    int capacity;
    int topIndex;

public:
    myStack(int size) {
        if (size <= 0)
            throw invalid_argument("Stack size must be positive.");

        capacity = size;
        arr = new T[capacity];
        topIndex = -1;
    }

    myStack(const myStack&) = delete;
    myStack& operator=(const myStack&) = delete;

    ~myStack() override {
        delete[] arr;
    }

    void push(T value) override {
        if (isFull())
            throw overflow_error("Stack is full.");

        arr[++topIndex] = value;
    }

    T pop() override {
        if (isEmpty())
            throw underflow_error("Stack is empty.");

        return arr[topIndex--];
    }

    T top() const override {
        if (isEmpty())
            throw underflow_error("Stack is empty.");

        return arr[topIndex];
    }

    bool isEmpty() const override {
        return topIndex == -1;
    }

    bool isFull() const override {
        return topIndex == capacity - 1;
    }

    void display() const {
        if (isEmpty()) {
            cout << "Stack is empty.\n";
            return;
        }

        cout << "Stack (top to bottom): ";
        for (int i = topIndex; i >= 0; i--)
            cout << arr[i] << " ";

        cout << '\n';
    }
};

#endif
