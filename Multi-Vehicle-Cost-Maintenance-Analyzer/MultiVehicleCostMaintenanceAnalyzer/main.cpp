#include <iostream>
#include "menu.h"
#include "structures.h"

using namespace std;

// Shared arrays
Vehicle vehicles[MAX_VEHICLES];
FuelRecord fuelRecords[MAX_RECORDS];
MaintenanceRecord maintenanceRecords[MAX_RECORDS];

// Record counts
int vehicleCount = 0;
int fuelRecordCount = 0;
int maintenanceRecordCount = 0;

int main()
{
    menu();

    return 0;
}