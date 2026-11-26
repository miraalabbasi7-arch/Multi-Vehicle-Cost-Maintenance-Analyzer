#pragma once

#ifndef FUEL_H
#define FUEL_H

#include <string>
#include "structures.h"

using namespace std;

const int ALL_VEHICLES = -1;

struct EfficiencyResult
{
    int vehicleID;
    int intervals;
    double distance;
    double litresUsed;
    double kmPerL;
    bool valid;
};

struct MonthlySpend
{
    string month;
    double total;
};


bool isValidDate(const string& date);

int findVehicleIndex(
	const Vehicle* vehicles,
    int vehicleCount,
    int vehicleID
);

bool validateFuelRecord(
    const FuelRecord& record,
    const Vehicle* vehicles,
    int vehicleCount,
    const FuelRecord* Fuel,
    int fuelCount,
    string& errorMessage
);

bool addFuelRecord(
    Vehicle* vehicles,
    int vehicleCount,
    FuelRecord* fuel,
    int& fuelCount,
    int fuelCapacity,
    const FuelRecord& record,
    string& errorMessage
);


double calculateFuelCost(const FuelRecord& record);

double totalFuelCost(const FuelRecord* fuel, int fuelCount, int vehicleID);

double totalFuelLitres(const FuelRecord* fuel, int fuelCount, int vehicleID);



void displayFuelHistory(
    const Vehicle* vehicles,
    int vehicleCount,
    const FuelRecord* fuel,
    int FuelCount,
    int VehicleID
);


void fuelTrackingMenu(
    Vehicle* vehicles,
    int vehicleCount,
    FuelRecord* fuel,
    int& fuelCount,
    int fuelCapacity
);

void fuelEfficiencyMenu(
    const Vehicle* vehicles,
    int vehicleCount,
    const FuelRecord* fuel,
    int fuelCount
);






#endif
