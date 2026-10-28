#include <iostream>
#include <string>
#include <stdexcept>
#include "myStack.h"
using namespace std;

struct EditAction {
    char character = '\0';
    int type = 0;
    // type 1 = typed a character
    // type 2 = deleted a character
};

void clearStack(myStack<EditAction>& s) {
    while (!s.isEmpty())
        s.pop();
}

int main() {
    string text = "";

    // Maximum number of undo/redo actions.
    myStack<EditAction> undoStack(1000);
    myStack<EditAction> redoStack(1000);

    int choice;
    string input;
    char ch;

    do {
        cout << "\n===== TEXT EDITOR MENU =====\n";
        cout << "Current text: [" << text << "]\n";
        cout << "1. Type text\n";
        cout << "2. Delete last character\n";
        cout << "3. Undo\n";
        cout << "4. Redo\n";
        cout << "5. Display current text\n";
        cout << "6. Exit\n";
        cout << "Enter choice: ";

        if (!(cin >> choice)) {
            cout << "Invalid input.\n";
            break;
        }

        try {
            switch (choice) {
            case 1:
                cout << "Enter text to add: ";
                cin >> ws;
                getline(cin, input);

                for (char c : input) {
                    EditAction action;
                    action.character = c;
                    action.type = 1;

                    undoStack.push(action);
                    text += c;
                }

                // A new edit invalidates the redo history.
                clearStack(redoStack);

                cout << "Text added successfully.\n";
                break;

            case 2:
                if (text.empty()) {
                    cout << "Nothing to delete.\n";
                    break;
                }

                ch = text.back();

                {
                    EditAction action;
                    action.character = ch;
                    action.type = 2;

                    undoStack.push(action);
                    text.pop_back();
                }

                clearStack(redoStack);
                cout << "Last character deleted.\n";
                break;

            case 3:
                if (undoStack.isEmpty()) {
                    cout << "Nothing to undo.\n";
                    break;
                }

                {
                    EditAction action = undoStack.pop();

                    if (action.type == 1) {
                        // Undo typing.
                        if (!text.empty())
                            text.pop_back();
                    }
                    else {
                        // Undo deletion.
                        text += action.character;
                    }

                    redoStack.push(action);
                }

                cout << "Undo successful.\n";
                break;

            case 4:
                if (redoStack.isEmpty()) {
                    cout << "Nothing to redo.\n";
                    break;
                }

                {
                    EditAction action = redoStack.pop();

                    if (action.type == 1) {
                        // Redo typing.
                        text += action.character;
                    }
                    else {
                        // Redo deletion.
                        if (!text.empty())
                            text.pop_back();
                    }

                    undoStack.push(action);
                }

                cout << "Redo successful.\n";
                break;

            case 5:
                cout << "Current text: " << text << '\n';
                break;

            case 6:
                cout << "Exiting text editor.\n";
                break;

            default:
                cout << "Invalid choice.\n";
            }
        }
        catch (const exception& e) {
            cout << "Error: " << e.what() << '\n';
        }

    } while (choice != 6);

    return 0;
}