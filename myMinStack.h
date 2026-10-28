#ifndef myMinStack_H
#define myMinStack_H

#include "AbstractStack.h"
#include <iostream>
#include <stdexcept>
using namespace std;

template <typename T>
class myStack : public AbstractStack<T> {
private:
    T* arr;
    T* minArr;
    int capacity;
    int topIndex;
    int minIndex;

public:
    myStack(int size) {
        if (size <= 0)
            throw invalid_argument("Stack size must be positive.");

        capacity = size;
        arr = new T[capacity];

        try {
            minArr = new T[capacity];
        }
        catch (...) {
            delete[] arr;
            throw;
        }

        topIndex = -1;
        minIndex = -1;
    }

    myStack(const myStack&) = delete;
    myStack& operator=(const myStack&) = delete;

    ~myStack() override {
        delete[] arr;
        delete[] minArr;
    }

    void push(T value) override {
        if (isFull())
            throw overflow_error("Stack is full.");

        arr[++topIndex] = value;

        if (minIndex == -1 || value <= minArr[minIndex])
            minArr[++minIndex] = value;
    }

    T pop() override {
        if (isEmpty())
            throw underflow_error("Stack is empty.");

        T value = arr[topIndex--];

        if (value == minArr[minIndex])
            minIndex--;

        return value;
    }

    T top() const override {
        if (isEmpty())
            throw underflow_error("Stack is empty.");

        return arr[topIndex];
    }

    T getMin() const {
        if (isEmpty())
            throw underflow_error("Stack is empty.");

        return minArr[minIndex];
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
