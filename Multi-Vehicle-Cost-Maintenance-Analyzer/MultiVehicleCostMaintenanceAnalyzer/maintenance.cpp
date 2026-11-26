#include <iostream>
#include <ctime>
#include <cstdio>
#include "maintenance.h"

using namespace std;

void addMaintenanceRecord()
{
    if (maintenanceRecordCount >= MAX_RECORDS)
    {
        cout << "Maintenance record limit reached!\n";
        return;
    }

    if (vehicleCount == 0)
    {
        cout << "No registered vehicles available!\n";
        return;
    }

    cout << "\n--- REGISTERED VEHICLES ---\n";

    for (int i = 0; i < vehicleCount; i++)
    {
        cout << i + 1 << ". "
            << vehicles[i].brand << " "
            << vehicles[i].model
            << " (ID: " << vehicles[i].vehicleID << ")\n";
    }

    int choice;

    cout << "\nSelect vehicle: ";
    cin >> choice;

    if (choice < 1 || choice > vehicleCount)
    {
        cout << "Invalid selection!\n";
        return;
    }

    int index = choice - 1;

    MaintenanceRecord& record =
        maintenanceRecords[maintenanceRecordCount];

    record.vehicleID = vehicles[index].vehicleID;
    record.odometer = vehicles[index].currentOdometer;

    int typeChoice;

    cout << "\n--- MAINTENANCE TYPE ---\n";
    cout << "1. Engine Oil Change\n";
    cout << "2. Oil Filter\n";
    cout << "3. Air Filter\n";
    cout << "4. Brake Inspection\n";
    cout << "5. General Service\n";

    cout << "Select maintenance type: ";
    cin >> typeChoice;

    switch (typeChoice)
    {
    case 1:
        record.maintenanceType = "Engine Oil Change";
        record.interval = 5000;
        break;

    case 2:
        record.maintenanceType = "Oil Filter";
        record.interval = 5000;
        break;

    case 3:
        record.maintenanceType = "Air Filter";
        record.interval = 10000;
        break;

    case 4:
        record.maintenanceType = "Brake Inspection";
        record.interval = 10000;
        break;

    case 5:
        record.maintenanceType = "General Service";
        record.interval = 5000;
        break;

    default:
        cout << "Invalid maintenance type!\n";
        return;
    }

    cout << "\nEnter maintenance cost (0 if unknown): ";
    cin >> record.cost;

    if (record.cost < 0)
    {
        cout << "Invalid cost!\n";
        return;
    }

    // Automatically get current date
    time_t now = time(0);
    tm localTime;
    localtime_s(&localTime, &now);

    char date[11];

    sprintf_s(date, "%02d/%02d/%04d",
        localTime.tm_mday,
        localTime.tm_mon + 1,
        localTime.tm_year + 1900);

    record.date = date;

    maintenanceRecordCount++;

    cout << "\nMaintenance record added successfully!\n";
}

void displayMaintenanceRecords()
{
    if (maintenanceRecordCount == 0)
    {
        cout << "No maintenance records available!\n";
        return;
    }

    for (int i = 0; i < maintenanceRecordCount; i++)
    {
        cout << "\n--- Maintenance Record " << i + 1 << " ---\n";

        cout << "Vehicle ID: " << maintenanceRecords[i].vehicleID << endl;
        cout << "Date: " << maintenanceRecords[i].date << endl;
        cout << "Maintenance Type: " << maintenanceRecords[i].maintenanceType << endl;
        cout << "Cost: " << maintenanceRecords[i].cost << endl;
        cout << "Odometer: " << maintenanceRecords[i].odometer << endl;
        cout << "Maintenance Interval: " << maintenanceRecords[i].interval << " km\n";
    }
}


void calculateNextMaintenance()
{
    int id;
    bool found = false;

    cout << "Enter Vehicle ID: ";
    cin >> id;

    for (int i = maintenanceRecordCount - 1; i >= 0; i--)
    {
        if (maintenanceRecords[i].vehicleID == id)
        {
            double nextDue = maintenanceRecords[i].odometer
                + maintenanceRecords[i].interval;

            cout << "\nNext Maintenance Due At: "
                << nextDue << " km\n";

            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "No maintenance record found for this vehicle!\n";
    }
}


void checkMaintenanceStatus()
{
    int id;
    bool found = false;

    cout << "Enter Vehicle ID: ";
    cin >> id;

    for (int i = maintenanceRecordCount - 1; i >= 0; i--)
    {
        if (maintenanceRecords[i].vehicleID == id)
        {
            double nextDue = maintenanceRecords[i].odometer
                + maintenanceRecords[i].interval;

            double currentOdometer = 0;

            for (int j = 0; j < vehicleCount; j++)
            {
                if (vehicles[j].vehicleID == id)
                {
                    currentOdometer = vehicles[j].currentOdometer;
                    found = true;
                    break;
                }
            }

            if (!found)
            {
                cout << "Vehicle not found!\n";
                return;
            }

            double remaining = nextDue - currentOdometer;

            cout << "\nRemaining Distance: " << remaining << " km\n";

            if (remaining <= 0)
                cout << "Status: OVERDUE\n";
            else if (remaining <= 500)
                cout << "Status: UPCOMING\n";
            else
                cout << "Status: NORMAL\n";

            found = true;
            break;
        }
    }

    if (!found)
        cout << "No maintenance record found for this vehicle!\n";
}