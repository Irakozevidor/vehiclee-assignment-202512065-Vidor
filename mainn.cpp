#include "vehicle.h"

int main() {
    int choice;

    cout << "===========================================\n";
    cout << "  Vehicle Registration & Owner Management  \n";
    cout << "===========================================\n";

    do {
        cout << "\n1. Add new vehicle record\n"
             << "2. Display all records\n"
             << "3. Search by plate number\n"
             << "4. Exit\n"
             << "Choice: ";
        cin  >> choice;
        cin.ignore();

        switch (choice) {
            case 1:
                addRecord();
                break;
            case 2:
                displayAll();
                break;
            case 3: {
                string plate;
                cout << "Enter plate number: ";
                cin  >> plate;
                searchByPlate(plate);
                break;
            }
            case 4:
                cout << "Goodbye!\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 4);

    return 0;
}
