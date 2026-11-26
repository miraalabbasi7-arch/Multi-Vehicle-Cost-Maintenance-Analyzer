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
        cout << "\nNo maintenance records available!\n";
        return;
    }

    cout << "\n";
    cout << "============================================\n";
    cout << "          MAINTENANCE HISTORY\n";
    cout << "============================================\n";

    for (int i = 0; i < maintenanceRecordCount; i++)
    {
        cout << "\nRecord #" << i + 1 << "\n";
        cout << "--------------------------------------------\n";

        // Find the vehicle details using its ID
        bool vehicleFound = false;

        for (int j = 0; j < vehicleCount; j++)
        {
            if (vehicles[j].vehicleID ==
                maintenanceRecords[i].vehicleID)
            {
                cout << "Vehicle: "
                    << vehicles[j].brand << " "
                    << vehicles[j].model << "\n";

                cout << "Vehicle ID: "
                    << vehicles[j].vehicleID << "\n";

                vehicleFound = true;
                break;
            }
        }

        if (!vehicleFound)
        {
            cout << "Vehicle ID: "
                << maintenanceRecords[i].vehicleID
                << " (Vehicle details unavailable)\n";
        }

        cout << "Maintenance Type: "
            << maintenanceRecords[i].maintenanceType << "\n";

        cout << "Service Date: "
            << maintenanceRecords[i].date << "\n";

        cout << "Odometer Reading: "
            << maintenanceRecords[i].odometer << " km\n";

        cout << "Service Interval: "
            << maintenanceRecords[i].interval << " km\n";

        if (maintenanceRecords[i].cost == 0)
        {
            cout << "Maintenance Cost: Not provided\n";
        }
        else
        {
            cout << "Maintenance Cost: "
                << maintenanceRecords[i].cost << "\n";
        }

        cout << "--------------------------------------------\n";
    }
}



void calculateNextMaintenance()
{
    if (maintenanceRecordCount == 0)
    {
        cout << "No maintenance records available!\n";
        return;
    }

    int id;
    bool vehicleFound = false;

    cout << "Enter Vehicle ID: ";
    cin >> id;

    double currentOdometer = 0;

    for (int i = 0; i < vehicleCount; i++)
    {
        if (vehicles[i].vehicleID == id)
        {
            currentOdometer = vehicles[i].currentOdometer;
            vehicleFound = true;
            break;
        }
    }

    if (!vehicleFound)
    {
        cout << "Vehicle not found!\n";
        return;
    }

    cout << "\n--- NEXT MAINTENANCE DUE ---\n";

    bool recordFound = false;

    for (int i = maintenanceRecordCount - 1; i >= 0; i--)
    {
        if (maintenanceRecords[i].vehicleID != id)
            continue;

        bool alreadyDisplayed = false;

        for (int j = i + 1; j < maintenanceRecordCount; j++)
        {
            if (maintenanceRecords[j].vehicleID == id &&
                maintenanceRecords[j].maintenanceType ==
                maintenanceRecords[i].maintenanceType)
            {
                alreadyDisplayed = true;
                break;
            }
        }

        if (alreadyDisplayed)
            continue;

        double nextDue = maintenanceRecords[i].odometer
            + maintenanceRecords[i].interval;

        cout << "\nMaintenance Type: "
            << maintenanceRecords[i].maintenanceType;

        cout << "\nNext Due At: " << nextDue << " km";

        cout << "\nRemaining Distance: "
            << nextDue - currentOdometer << " km\n";

        recordFound = true;
    }

    if (!recordFound)
    {
        cout << "No maintenance records found for this vehicle!\n";
    }
}




void checkMaintenanceStatus()
{
    if (vehicleCount == 0)
    {
        cout << "\nNo registered vehicles available!\n";
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
    int id = vehicles[index].vehicleID;

    if (maintenanceRecordCount == 0)
    {
        cout << "\nNo maintenance records available!\n";
        return;
    }

    cout << "\n====================================\n";
    cout << "       MAINTENANCE STATUS\n";
    cout << "====================================\n";

    bool recordFound = false;

    for (int i = maintenanceRecordCount - 1; i >= 0; i--)
    {
        if (maintenanceRecords[i].vehicleID != id)
            continue;

        bool alreadyDisplayed = false;

        for (int j = i + 1; j < maintenanceRecordCount; j++)
        {
            if (maintenanceRecords[j].vehicleID == id &&
                maintenanceRecords[j].maintenanceType ==
                maintenanceRecords[i].maintenanceType)
            {
                alreadyDisplayed = true;
                break;
            }
        }

        if (alreadyDisplayed)
            continue;

        double nextDue =
            maintenanceRecords[i].odometer +
            maintenanceRecords[i].interval;

        double remaining =
            nextDue - vehicles[index].currentOdometer;

        cout << "\nMaintenance: "
            << maintenanceRecords[i].maintenanceType;

        cout << "\nNext Due At: "
            << nextDue << " km";

        cout << "\nRemaining Distance: "
            << remaining << " km";

        if (remaining <= 0)
            cout << "\nStatus: OVERDUE\n";
        else if (remaining <= 500)
            cout << "\nStatus: UPCOMING\n";
        else
            cout << "\nStatus: NORMAL\n";

        cout << "------------------------------------\n";

        recordFound = true;
    }

    if (!recordFound)
    {
        cout << "\nNo maintenance records found for this vehicle!\n";
    }
}
