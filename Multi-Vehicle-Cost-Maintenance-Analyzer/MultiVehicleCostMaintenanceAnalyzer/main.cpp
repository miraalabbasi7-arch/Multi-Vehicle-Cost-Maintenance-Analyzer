#include <iostream>
#include "menu.h"
#include "structures.h"
using namespace std;

Vehicle vehicles[MAX_VEHICLES];
FuelRecord fuelRecords[MAX_RECORDS];
MaintenanceRecord maintenanceRecords[MAX_RECORDS];

int vehicleCount = 0;
int fuelRecordCount = 0;
int maintenanceRecordCount = 0;

int main() {
   cout << menu();
    return 0;
}