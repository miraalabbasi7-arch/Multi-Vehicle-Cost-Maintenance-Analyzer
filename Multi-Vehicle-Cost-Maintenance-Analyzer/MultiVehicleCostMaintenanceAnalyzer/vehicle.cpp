#include <iostream>
#include <fstream>
#include <iomanip>
#include "vehicle.h"

using namespace std;

void addVehicle(Vehicle* vehicles, int& vehicleCount) {
    if (vehicleCount >= MAX_VEHICLES) {
        cout << "\n[Error] Maximum vehicle limit reached!\n";
        return;
    }

    Vehicle newV;
    cout << "\n--- Register New Vehicle ---\n";
    cout << "Enter Vehicle ID (positive number): ";
    cin >> newV.vehicleID;

    if (cin.fail() || newV.vehicleID <= 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "[Error] Invalid ID! Must be a positive number.\n";
        return;
    }

    for (int i = 0; i < vehicleCount; i++) {
        if ((vehicles + i)->vehicleID == newV.vehicleID) {
            cout << "[Error] Vehicle ID already exists!\n";
            return;
        }
    }

    cin.ignore(1000, '\n');
    cout << "Enter Vehicle Name (e.g. Civic): ";
    getline(cin, newV.name);
    cout << "Enter Brand (e.g. Honda): ";
    getline(cin, newV.brand);
    cout << "Enter Model Year (e.g. 2022): ";
    getline(cin, newV.model);
    cout << "Enter Type (Car/Motorcycle): ";
    getline(cin, newV.type);

    cout << "Enter Current Odometer (km): ";
    cin >> newV.currentOdometer;

    if (cin.fail() || newV.currentOdometer < 0) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "[Error] Odometer reading cannot be negative!\n";
        return;
    }

    *(vehicles + vehicleCount) = newV;
    vehicleCount++;
    cout << "[Success] Vehicle added successfully!\n";
}

void viewAllVehicles(const Vehicle* vehicles, int vehicleCount) {
    if (vehicleCount == 0) {
        cout << "\nNo vehicles registered yet.\n";
        return;
    }

    cout << "\n====================================================================\n";
    cout << left << setw(8) << "ID" << setw(15) << "Name" << setw(14) << "Brand"
        << setw(10) << "Model" << setw(13) << "Type" << "Odometer (km)\n";
    cout << "====================================================================\n";

    for (int i = 0; i < vehicleCount; i++) {
        cout << left << setw(8) << (vehicles + i)->vehicleID
            << setw(15) << (vehicles + i)->name
            << setw(14) << (vehicles + i)->brand
            << setw(10) << (vehicles + i)->model
            << setw(13) << (vehicles + i)->type
            << (vehicles + i)->currentOdometer << "\n";
    }
    cout << "====================================================================\n";
}

void searchVehicleByID(const Vehicle* vehicles, int vehicleCount) {
    if (vehicleCount == 0) {
        cout << "\nNo vehicles available to search.\n";
        return;
    }

    int searchID;
    cout << "\nEnter Vehicle ID to search: ";
    cin >> searchID;

    if (cin.fail()) {
        cin.clear();
        cin.ignore(1000, '\n');
        cout << "[Error] Please enter a valid numeric ID.\n";
        return;
    }

    for (int i = 0; i < vehicleCount; i++) {
        if ((vehicles + i)->vehicleID == searchID) {
            cout << "\n--- Vehicle Found ---\n";
            cout << "ID: " << (vehicles + i)->vehicleID << "\n";
            cout << "Name: " << (vehicles + i)->name << "\n";
            cout << "Brand: " << (vehicles + i)->brand << "\n";
            cout << "Model: " << (vehicles + i)->model << "\n";
            cout << "Type: " << (vehicles + i)->type << "\n";
            cout << "Odometer: " << (vehicles + i)->currentOdometer << " km\n";
            return;
        }
    }
    cout << "[Not Found] No vehicle with ID " << searchID << ".\n";
}

void saveVehiclesToFile(const Vehicle* vehicles, int vehicleCount) {
    ofstream outFile("vehicles.txt");
    if (!outFile) return;

    outFile << vehicleCount << "\n";
    for (int i = 0; i < vehicleCount; i++) {
        outFile << (vehicles + i)->vehicleID << "\n"
            << (vehicles + i)->name << "\n"
            << (vehicles + i)->brand << "\n"
            << (vehicles + i)->model << "\n"
            << (vehicles + i)->type << "\n"
            << (vehicles + i)->currentOdometer << "\n";
    }
    outFile.close();
}

void loadVehiclesFromFile(Vehicle* vehicles, int& vehicleCount) {
    ifstream inFile("vehicles.txt");
    if (!inFile) return;

    inFile >> vehicleCount;
    inFile.ignore(1000, '\n');
    for (int i = 0; i < vehicleCount && i < MAX_VEHICLES; i++) {
        inFile >> (vehicles + i)->vehicleID;
        inFile.ignore(1000, '\n');
        getline(inFile, (vehicles + i)->name);
        getline(inFile, (vehicles + i)->brand);
        getline(inFile, (vehicles + i)->model);
        getline(inFile, (vehicles + i)->type);
        inFile >> (vehicles + i)->currentOdometer;
        inFile.ignore(1000, '\n');
    }
    inFile.close();
}

void vehicleMenu(Vehicle* vehicles, int& vehicleCount) {
    int subChoice = 0;
    while (subChoice != 4) {
        cout << "\n--- VEHICLE PROFILE MANAGEMENT ---\n";
        cout << "1. Add New Vehicle\n";
        cout << "2. View All Vehicles\n";
        cout << "3. Search Vehicle by ID\n";
        cout << "4. Back to Main Menu\n";
        cout << "Select option (1-4): ";
        cin >> subChoice;

        if (cin.fail()) {
            cin.clear();
            cin.ignore(1000, '\n');
            cout << "[Error] Please enter a number (1-4)!\n";
            continue;
        }

        if (subChoice == 1) addVehicle(vehicles, vehicleCount);
        else if (subChoice == 2) viewAllVehicles(vehicles, vehicleCount);
        else if (subChoice == 3) searchVehicleByID(vehicles, vehicleCount);
        else if (subChoice != 4) cout << "Invalid choice!\n";
    }
}