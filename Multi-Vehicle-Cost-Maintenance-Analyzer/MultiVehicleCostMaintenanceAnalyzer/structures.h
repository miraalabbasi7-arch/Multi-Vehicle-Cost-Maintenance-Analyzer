#pragma once

#include <string>
using namespace std;

const int MAX_VEHICLES = 50;
const int MAX_RECORDS = 200;

struct Vehicle
{
    int vehicleID;
    string name;
    string brand;
    string model;
    string type;
    double currentOdometer;
};

struct FuelRecord
{
    int vehicleID;
    string date;
    double litres;
    double pricePerLitre;
    double odometer;
    bool fullTank;
};

struct MaintenanceRecord
{
    int vehicleID;
    string date;
    string maintenanceType;
    double cost;
    double odometer;
    double interval;
};

// Shared arrays
extern Vehicle vehicles[MAX_VEHICLES];
extern FuelRecord fuelRecords[MAX_RECORDS];
extern MaintenanceRecord maintenanceRecords[MAX_RECORDS];

// Record counts
extern int vehicleCount;
extern int fuelRecordCount;
extern int maintenanceRecordCount;

