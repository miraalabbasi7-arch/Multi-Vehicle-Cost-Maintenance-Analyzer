#include <iostream>
#include "maintenance.h"

using namespace std;

void addMaintenanceRecord()
{
    if (maintenanceRecordCount >= MAX_RECORDS)
    {
        cout << "Maintenance record limit reached!\n";
        return;
    }

    int id;
    bool found = false;

    cout << "Enter Vehicle ID: ";
    cin >> id;

    for (int i = 0; i < vehicleCount; i++)
    {
        if (vehicles[i].vehicleID == id)
        {
            found = true;
            break;
        }
    }

    if (!found)
    {
        cout << "Vehicle not found!\n";
        return;
    }

    MaintenanceRecord& record = maintenanceRecords[maintenanceRecordCount];

    record.vehicleID = id;

    cout << "Enter maintenance date (DD/MM/YYYY): ";
    cin >> record.date;

    cout << "Enter maintenance type: ";
    cin >> record.maintenanceType;

    cout << "Enter maintenance cost: ";
    cin >> record.cost;

    cout << "Enter odometer reading: ";
    cin >> record.odometer;

    cout << "Enter maintenance interval (km): ";
    cin >> record.interval;

    if (record.cost <= 0 || record.odometer <= 0 || record.interval <= 0)
    {
        cout << "Invalid values! Record not saved.\n";
        return;
    }

    maintenanceRecordCount++;

    cout << "Maintenance record added successfully!\n";

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