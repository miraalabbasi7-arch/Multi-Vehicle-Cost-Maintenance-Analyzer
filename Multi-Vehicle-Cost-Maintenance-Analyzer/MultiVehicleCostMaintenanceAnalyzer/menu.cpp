#include <iostream>
#include <iomanip>
#include "menu.h"
#include "vehicle.h"

using namespace std;

int menu() {
    Vehicle vehicles[MAX_VEHICLES];
    FuelRecord fuelRecords[MAX_RECORDS];
    MaintenanceRecord maintenanceRecords[MAX_RECORDS];

    int vehicleCount = 0;
    double totalExpenses = 0.0;
    int choice = 0;

    loadVehiclesFromFile(vehicles, vehicleCount);

    while (choice != 8) {
        cout << "\n+==============================================================+\n";
        cout << "|                       VEHICLE ANALYZER                       |\n";
        cout << "|                   COST * FUEL * MAINTENANCE                  |\n";
        cout << "+==============================================================+\n";
        cout << "| REGISTERED VEHICLES: " << left << setw(12) << vehicleCount
            << "TOTAL EXPENSES: " << setw(12) << totalExpenses << "|\n";
        cout << "+==============================================================+\n";
        cout << "|                          MAIN MENU                           |\n";
        cout << "+==============================================================+\n";
        cout << "|  01  Vehicle Profiles                                        |\n";
        cout << "|  02  Fuel Tracking                                           |\n";
        cout << "|  03  Fuel Efficiency Analysis                                |\n";
        cout << "|  04  Maintenance Analyzer                                    |\n";
        cout << "|  05  Expense Analysis                                        |\n";
        cout << "|  06  Graphical Reports                                       |\n";
        cout << "|  07  Save / Load Data                                        |\n";
        cout << "|  08  Exit                                                    |\n";
        cout << "+==============================================================+\n";
        cout << "Select an option (1-8): ";
        cin >> choice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "-> Invalid input! Please enter a number (1-8).\n";
            continue;
        }

        if (choice == 1) {
            vehicleMenu(vehicles, vehicleCount);
        }
        else if (choice == 2) cout << "-> Fuel Tracking\n";
        else if (choice == 3) cout << "-> Fuel Efficiency Analysis\n";
        else if (choice == 4) cout << "-> Maintenance Analyzer\n";
        else if (choice == 5) cout << "-> Expense Analysis\n";
        else if (choice == 6) cout << "-> Graphical Reports\n";
        else if (choice == 7) {
            saveVehiclesToFile(vehicles, vehicleCount);
            cout << "-> Vehicle data saved successfully!\n";
        }
        else if (choice == 8) {
            saveVehiclesToFile(vehicles, vehicleCount);
            cout << "-> Data saved. Exiting...\n";
        }
        else cout << "-> Invalid option! Choose 1 to 8.\n";
    }

    return 0;
}