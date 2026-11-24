#include <iostream>
using namespace std;

int main() {
    int vehicles;
    int expensesK;
    int choice = 0;

    while (choice != 8) {
        cout << "\n+--------------------------------------------------------------+\n";
        cout << "|                       VEHICLE ANALYZER                       |\n";
        cout << "|                   COST * FUEL * MAINTENANCE                  |\n";
        cout << "+==============================================================+\n";
        cout << "|  REGISTERED VEHICLES: "
            << "             TOTAL EXPENSES: " << "          |\n";
        cout << "+==============================================================+\n";
        cout << "|                          MAIN MENU                           |\n";
        cout << "|                                                              |\n";
        cout << "|    01  Vehicle Profiles                                      |\n";
        cout << "|    02  Fuel Tracking                                         |\n";
        cout << "|    03  Fuel Efficiency Analysis                              |\n";
        cout << "|    04  Maintenance Analyzer                                  |\n";
        cout << "|    05  Expense Analysis                                      |\n";
        cout << "|    06  Graphical Reports                                     |\n";
        cout << "|    07  Save / Load Data                                      |\n";
        cout << "|    08  Exit                                                  |\n";
        cout << "|                                                              |\n";
        cout << "+==============================================================+\n";
        cout << "Select an option (1-8): ";
        cin >> choice;

        if (choice == 1)      cout << "-> Vehicle Profiles\n";
        else if (choice == 2) cout << "-> Fuel Tracking\n";
        else if (choice == 3) cout << "-> Fuel Efficiency Analysis\n";
        else if (choice == 4) cout << "-> Maintenance Analyzer\n";
        else if (choice == 5) cout << "-> Expense Analysis\n";
        else if (choice == 6) cout << "-> Graphical Reports\n";
        else if (choice == 7) cout << "-> Save / Load Data\n";
        else if (choice == 8) cout << "-> Exiting...\n";
        else                  cout << "-> Invalid option! Choose 1 to 8.\n";
    }

    return 0;
}