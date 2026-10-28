#ifndef MYCARSTACK_H
#define MYCARSTACK_H

#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

class myCarStack {
private:
    string* cars;
    int capacity;
    int topIndex;

public:
    myCarStack(int size = 8) {
        if (size <= 0)
            throw invalid_argument("Capacity must be positive.");

        capacity = size;
        cars = new string[capacity];
        topIndex = -1;
    }

    myCarStack(const myCarStack&) = delete;
    myCarStack& operator=(const myCarStack&) = delete;

    ~myCarStack() {
        delete[] cars;
    }

    bool isEmpty() const {
        return topIndex == -1;
    }

    bool isFull() const {
        return topIndex == capacity - 1;
    }

    int count() const {
        return topIndex + 1;
    }

    void push(const string& car) {
        if (isFull())
            throw overflow_error("Parking lot is full.");

        cars[++topIndex] = car;
    }

    string pop() {
        if (isEmpty())
            throw underflow_error("Parking lot is empty.");

        return cars[topIndex--];
    }

    string top() const {
        if (isEmpty())
            throw underflow_error("No cars are parked.");

        return cars[topIndex];
    }

    bool search(const string& car) const {
        for (int i = 0; i <= topIndex; i++) {
            if (cars[i] == car)
                return true;
        }

        return false;
    }

    void display() const {
        if (isEmpty()) {
            cout << "No cars are parked.\n";
            return;
        }

        cout << "\nCars from top to bottom:\n";
        for (int i = topIndex; i >= 0; i--)
            cout << cars[i] << '\n';
    }

    bool removeCar(const string& car) {
        if (!search(car))
            return false;

        myCarStack temp(capacity);

        while (top() != car)
            temp.push(pop());

        pop();  // Remove the requested car.

        while (!temp.isEmpty())
            push(temp.pop());

        return true;
    }
};

#endif
