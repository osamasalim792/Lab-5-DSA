#include <iostream>
#include <string>
#include <limits>
#include <stdexcept>
#include "myCarStack.h"
using namespace std;

int main() {
    myCarStack parking(8);
    int choice;
    string car;

    do {
        cout << "\n===== PARKING LOT MENU =====\n";
        cout << "1. Park a new car\n";
        cout << "2. Remove a car by number\n";
        cout << "3. Search for a car\n";
        cout << "4. Display parked cars\n";
        cout << "5. Show total cars parked\n";
        cout << "6. Show car at the exit (top)\n";
        cout << "7. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input.\n";
            break;
        }

        try {
            switch (choice) {
            case 1:
                if (parking.isFull()) {
                    cout << "Parking lot is full. No space available.\n";
                    break;
                }

                cout << "Enter car number/license plate: ";
                cin >> ws;
                getline(cin, car);

                if (car.empty()) {
                    cout << "Car number cannot be empty.\n";
                    break;
                }

                if (parking.search(car)) {
                    cout << "This car is already parked.\n";
                    break;
                }

                parking.push(car);
                cout << "Car parked successfully.\n";
                break;

            case 2:
                cout << "Enter car number to remove: ";
                cin >> ws;
                getline(cin, car);

                if (parking.removeCar(car))
                    cout << "Car removed successfully.\n";
                else
                    cout << "Car not found.\n";
                break;

            case 3:
                cout << "Enter car number to search: ";
                cin >> ws;
                getline(cin, car);

                if (parking.search(car))
                    cout << "Car is present in the parking lot.\n";
                else
                    cout << "Car is not present.\n";
                break;

            case 4:
                parking.display();
                break;

            case 5:
                cout << "Total cars parked: "
                    << parking.count() << "/8\n";
                break;

            case 6:
                if (parking.isEmpty())
                    cout << "Parking lot is empty.\n";
                else
                    cout << "Top car: " << parking.top() << '\n';
                break;

            case 7:
                cout << "Exiting parking system.\n";
                break;

            default:
                cout << "Invalid choice.\n";
            }
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << '\n';
        }

    } while (choice != 7);

    return 0;
}