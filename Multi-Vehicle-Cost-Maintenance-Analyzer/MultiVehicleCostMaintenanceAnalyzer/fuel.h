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


EfficiencyResult calculateVehicleEfficiency(
	const FuelRecord* fuel,
	int fuelCount,
	int vehicleID
);


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



int loadFuelRecords(FuelRecord* fuel, int fuelCapacity,
    const Vehicle* vehicles, int vehicleCount, int& skipped,
    const string& filename = "fuel.txt");


bool saveFuelRecords(const FuelRecord* fuel, int fuelCount, const string& filename = "fuel.txt");


bool calculateKmPerL(double distance, double liters, double& kmPerL);


double calculateFuelCost(const FuelRecord& record);

double totalFuelCost(const FuelRecord* fuel, int fuelCount, int vehicleID);

double totalFuelLitres(const FuelRecord* fuel, int fuelCount, int vehicleID);

double calculateDistance(double previousOdometer, double currentOdometer);



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

void displayFuelSpendingSummary(
  const Vehicle* vehicles,
    int vehicleCount,
	const FuelRecord* fuel,
    int fuelCount
);

void calculateAllEfficiencies(
    const Vehicle* vehicles,
    int vehicleCount,
    const FuelRecord* fuel,
    int fuelCount,
    EfficiencyResult* results);


void displayEfficiencyDetails(
    const Vehicle* vehicles,
    int vehicleCount,
    const FuelRecord* fuel,
    int fuelCount,
    int vehicleID);


int findMostEfficientVehicle(
    const EfficiencyResult* results,
    int count);


void displayEfficiencyComparison(
    const Vehicle* vehicles,
    int vehicleCount,
    const FuelRecord* fuel,
    int fuelCount);


void displayEfficiencyGraph(
    const Vehicle* vehicles,
    int vehicleCount,
    const FuelRecord* fuel,
    int fuelCount);


int getMonthlyFuelSpending(
    const FuelRecord* fuel,
    int fuelCount,
    int vehicleID,
    MonthlySpend* out,
    int maxMonths);

void displayMonthlySpendingGraph(
    const Vehicle* vehicles,
    int vehicleCount,
    const FuelRecord* fuel,
    int fuelCount,
    int vehicleID);





#endif
