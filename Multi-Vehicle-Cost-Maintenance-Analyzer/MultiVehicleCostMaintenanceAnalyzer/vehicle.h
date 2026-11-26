#ifndef VEHICLE_H
#define VEHICLE_H

#include "structures.h"

void vehicleMenu(Vehicle* vehicles, int& vehicleCount);
void addVehicle(Vehicle* vehicles, int& vehicleCount);
void viewAllVehicles(const Vehicle* vehicles, int vehicleCount);
void searchVehicleByID(const Vehicle* vehicles, int vehicleCount);
void saveVehiclesToFile(const Vehicle* vehicles, int vehicleCount);
void loadVehiclesFromFile(Vehicle* vehicles, int& vehicleCount);

#endif
