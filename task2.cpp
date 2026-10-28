#include <iostream>
#include <stdexcept>
#include "myMinStack.h"
using namespace std;

int main() {
    int size;

    cout << "Enter maximum stack size: ";
    if (!(cin >> size) || size <= 0) {
        cout << "Invalid stack size.\n";
        return 1;
    }

    myStack<int> s(size);
    int choice, value;

    do {
        cout << "\n===== MINIMUM STACK MENU =====\n";
        cout << "1. Push element\n";
        cout << "2. Pop element\n";
        cout << "3. Show top element\n";
        cout << "4. Check if stack is empty\n";
        cout << "5. Check if stack is full\n";
        cout << "6. Display stack\n";
        cout << "7. Show minimum element\n";
        cout << "8. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input.\n";
            break;
        }

        try {
            switch (choice) {
            case 1:
                cout << "Enter value: ";
                if (!(cin >> value)) {
                    cout << "Invalid value.\n";
                    return 1;
                }
                s.push(value);
                cout << "Element pushed successfully.\n";
                break;

            case 2:
                cout << "Popped element: " << s.pop() << '\n';
                break;

            case 3:
                cout << "Top element: " << s.top() << '\n';
                break;

            case 4:
                cout << (s.isEmpty() ?
                    "Stack is empty.\n" :
                    "Stack is not empty.\n");
                break;

            case 5:
                cout << (s.isFull() ?
                    "Stack is full.\n" :
                    "Stack is not full.\n");
                break;

            case 6:
                s.display();
                break;

            case 7:
                cout << "Minimum element: " << s.getMin() << '\n';
                break;

            case 8:
                cout << "Exiting program.\n";
                break;

            default:
                cout << "Invalid choice.\n";
            }
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << '\n';
        }

    } while (choice != 8);

    return 0;
}