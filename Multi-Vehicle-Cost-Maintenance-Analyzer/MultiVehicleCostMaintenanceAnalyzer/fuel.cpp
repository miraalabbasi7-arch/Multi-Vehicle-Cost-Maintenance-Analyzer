#include "fuel.h"
#include <iostream>
#include <sstream>
#include <iomanip>

using namespace std;

bool isValidDate(const string& date) {
	
	if (date.length() != 10) {
		return false;
	}

	if (date[4] != '-' || date[7] != '-') {
		return false;
	}

	return true;
}



int findVehicleIndex(const Vehicle* vehicles, int vehicleCount, int vehicleID) {

	for (int i = 0; i < vehicleCount; i++) {
        if (vehicles[i].vehicleID == vehicleID) {
			return i;
		}
}
	return -1;
}



bool validateFuelRecord(
	const FuelRecord& record,
	const Vehicle* vehicles,
	int vehicleCount,
	const FuelRecord* fuel,
	int fuelCount,
	string& errorMessage)
{

	if (findVehicleIndex(vehicles, vehicleCount, record.vehicleID) == -1) {
	      
		errorMessage = "Vehicle ID does not exist.";
		return false;
	}

	if (!isValidDate(record.date)) {
		errorMessage = "Invalid date format. Use YYYY-MM-DD.";
		return false;
	}

	if (record.litres <= 0) {

		errorMessage = "Liters must be greater than 0.";
		return false;
	}
    
	if (record.odometer < 0) {
		errorMessage = "Odometer reading cannot be negative.";
		return false;
	}

	for (int i = 0; i < fuelCount; i++) {
		if (fuel[i].vehicleID == record.vehicleID && record.odometer < fuel[i].odometer) {
			errorMessage = "Odometer reading cannot decrease";
			return false;
		}
	}


	errorMessage = "";
	return true;

}




double calculateFuelCost(const FuelRecord& record) {
	return record.litres * record.pricePerLitre;
}	


double totalFuelCost(const FuelRecord* fuel, int fuelCount, int vehicleID) {

	double total = 0;

	for (int i = 0; i < fuelCount; i++) {
		if (fuel[i].vehicleID == vehicleID) {
			total += calculateFuelCost(fuel[i]);
		}
	}
	return total;

}


double totalFuelLitres(const FuelRecord* fuel, int fuelCount, int vehicleID) {

	double total = 0;

	for (int i = 0; i < fuelCount; i++) {
		if (fuel[i].vehicleID == vehicleID) {
			total += fuel[i].litres;
		}
	}
	return total;
}




bool addFuelRecord(
	Vehicle* vehicles,
	int vehicleCount,
	FuelRecord* fuel,
	int& fuelCount,
	int fuelCapacity,
	const FuelRecord& record,
	string& errorMessage)
{
	if (fuelCount >= fuelCapacity)
	{
		errorMessage = "Fuel records storage is full.";
		return false;
	}

	if (!validateFuelRecord(record, vehicles, vehicleCount,
		fuel, fuelCount, errorMessage))
	{
		return false;
	}

	fuel[fuelCount] = record;

	fuelCount++;

	errorMessage = "";
	return true;
}



void displayFuelHistory(
	const Vehicle* vehicles,
	int vehicleCount,
	const FuelRecord* fuel,
	int fuelCount,
	int vehicleID)
{
	int index = findVehicleIndex(vehicles, vehicleCount, vehicleID);
	if (index == -1)
	{
		cout << "Vehicle not found!\n";
		return;
	}

	bool hasRecords = false;

	for (int i = 0; i < fuelCount; i++)
	{
		if (fuel[i].vehicleID == vehicleID)
		{
			hasRecords = true;
			break;
		}
	}

	if (!hasRecords)
	{
		cout << "No fuel records found for this vehicle.\n";
		return;
	}

	cout << "\nFuel History for "
		<< vehicles[index].name << "\n";



	cout << "\n";
	cout << "---------------------------------------------------------------\n";

	cout << left
		<< setw(15) << "Date"
		<< setw(12) << "Litres"
		<< setw(15) << "Price/Litre"
		<< setw(15) << "Total Cost"
		<< setw(12) << "Odometer" << "\n";

	cout << "---------------------------------------------------------------\n";

	for (int i = 0; i < fuelCount; i++)
	{
		if (fuel[i].vehicleID == vehicleID)
		{
			cout << left
				<< setw(15) << fuel[i].date
				<< setw(12) << fuel[i].litres
				<< setw(15) << fuel[i].pricePerLitre
				<< setw(15) << calculateFuelCost(fuel[i])
				<< setw(12) << fuel[i].odometer
				<< "\n";
		}
	}


	double totalLitres = totalFuelLitres(fuel, fuelCount, vehicleID);

	double totalCost = totalFuelCost(fuel, fuelCount, vehicleID);

	cout << "---------------------------------------------------------------\n";

	cout << "Total Litres Purchased: " << totalLitres << " L\n";

	cout << "Total Fuel Spending: " << totalCost << "\n";

	cout << "---------------------------------------------------------------\n";



}


void fuelTrackingMenu(
	Vehicle* vehicles,
	int vehicleCount,
	FuelRecord* fuel,
	int& fuelCount,
	int fuelCapacity)
{
	int choice = 0;

	while (choice != 3)
	{
		cout << "\n===== FUEL TRACKING MENU =====\n";
		cout << "1. Add Fuel Record\n";
		cout << "2. Display Fuel History\n";
		cout << "3. Return to Main Menu\n";
		cout << "Enter choice: ";

		cin >> choice;

		if (choice == 1)
		{
			FuelRecord record;
			string errorMessage;

			cout << "Enter Vehicle ID: ";
			cin >> record.vehicleID;

			cout << "Enter Date (YYYY-MM-DD): ";
			cin >> record.date;

			cout << "Enter Litres: ";
			cin >> record.litres;

			cout << "Enter Price Per Litre: ";
			cin >> record.pricePerLitre;

			cout << "Enter Odometer Reading: ";
			cin >> record.odometer;

			if (addFuelRecord(
				vehicles, vehicleCount,
				fuel, fuelCount, fuelCapacity,
				record, errorMessage))
			{
				cout << "Fuel record added successfully!\n";
			}
			else
			{
				cout << "Error: " << errorMessage << "\n";
			}
		}
		else if (choice == 2)
		{
			int vehicleID;

			cout << "Enter Vehicle ID: ";
			cin >> vehicleID;

			displayFuelHistory(
				vehicles, vehicleCount,
				fuel, fuelCount, vehicleID);
		}
		else if (choice == 3)
		{
			cout << "Returning to Main Menu...\n";
		}
		else
		{
			cout << "Invalid choice!\n";
		}
	}
}


void fuelEfficiencyMenu(
	const Vehicle* vehicles,
	int vehicleCount,
	const FuelRecord* fuel,
	int fuelCount)
{
	cout << "\n===== FUEL EFFICIENCY MENU =====\n";
	cout << "Fuel efficiency features are under development.\n";
}


