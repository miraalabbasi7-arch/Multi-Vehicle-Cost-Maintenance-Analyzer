#include "fuel.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <fstream>

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

bool saveFuelRecords(const FuelRecord* fuel, int fuelCount,
	const string& filename)
{
	ofstream outFile(filename);
	if (!outFile) {
		cout << "Error unable to open Fuel file !\n";
		return false;
	}
	for (int i = 0; i < fuelCount; i++) {
		outFile << fuel[i].vehicleID << " "
			<< fuel[i].date << " "
			<< fuel[i].litres << " "
			<< fuel[i].pricePerLitre << " "
			<< fuel[i].odometer << " "
			<< fuel[i].fullTank << "\n";
	}
	outFile.close();
	cout << "Fuel records saved successfully!\n";
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

	cout << fixed << setprecision(2);

	cout << left
		<< setw(15) << "Date"
		<< setw(12) << "Litres"
		<< setw(15) << "Price/Litre"
		<< setw(15) << "Total Cost"
		<< setw(12) << "Odometer" 
		<< setw(15) << "Refill Type" << "\n";

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
				<< setw(15) << (fuel[i].fullTank ? "full Tank" : "Partial")
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

	while (choice != 6)
	{
		cout << "\n===== FUEL TRACKING MENU =====\n";
		cout << "1. Add Fuel Record\n";
		cout << "2. Display Fuel History\n";
		cout << "3. Display Fuel Spending Summary\n";
		cout << "4. Save Fuel Records\n";
		cout << "5. Monthly Fuel Spending Graph\n";
		cout << "6. Return to Main Menu\n";
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

	
			char refillType;

			do
			{
				cout << "Is this a full tank refill? (y/n): ";
				cin >> refillType;

				if (refillType != 'y' && refillType != 'Y' &&
					refillType != 'n' && refillType != 'N')
				{
					cout << "Invalid input! Enter y or n.\n";
				}

			} while (refillType != 'y' && refillType != 'Y' &&
				refillType != 'n' && refillType != 'N');

			record.fullTank = (refillType == 'y' || refillType == 'Y');
		


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
			displayFuelSpendingSummary(
				vehicles, vehicleCount,
				fuel, fuelCount);
		}
		else if (choice == 4)
		{
			saveFuelRecords(fuel,fuelCount);
		}
		else if (choice == 5) {
		  
			int vehicleID;

			cout << "Enter Vehicle ID (or -1 for all vehicles): ";
			cin >> vehicleID;

			displayMonthlySpendingGraph(
				vehicles, vehicleCount,
				fuel, fuelCount, vehicleID);
		
		}

		else if (choice == 6)
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
	int choice = 0;

	while (choice != 4)
	{
		cout << "\n===== FUEL EFFICIENCY MENU =====\n";
		cout << "1. View Vehicle Efficiency Details\n";
		cout << "2. Compare Vehicle Efficiency\n";
		cout << "3. Display Efficiency Graph\n";
		cout << "4. Return to Main Menu\n";
		cout << "Enter choice: ";

		cin >> choice;

		if (choice == 1)
		{
			int vehicleID;

			cout << "Enter Vehicle ID: ";
			cin >> vehicleID;

			displayEfficiencyDetails(
				vehicles, vehicleCount,
				fuel, fuelCount, vehicleID);
		}
		else if (choice == 2)
		{
			displayEfficiencyComparison(
				vehicles, vehicleCount,
				fuel, fuelCount);
		}
		else if (choice == 3)
		{
			displayEfficiencyGraph(
				vehicles, vehicleCount,
				fuel, fuelCount);
		}
		else if (choice == 4)
		{
			cout << "Returning to Main Menu...\n";
		}
		else
		{
			cout << "Invalid choice!\n";
		}
	}
}

void displayFuelSpendingSummary(
	const Vehicle* vehicles,
	int vehicleCount,
	const FuelRecord* fuel,
	int fuelCount)
{  

	if (vehicleCount == 0) {
		cout << "No vehicles registered.\n";
		return;
	}



	cout << "\n========== FUEL SPENDING SUMMARY ==========\n";

	cout << left
		<< setw(25) << "Vehicle"
		<< setw(20) << "Total Spending" << "\n";

	cout << "---------------------------------------------\n";


	for (int i = 0; i < vehicleCount; i++)
	{
		double spending = totalFuelCost(fuel, fuelCount, vehicles[i].vehicleID);
		cout <<left
			<< setw(25) << vehicles[i].name
			<< setw(20) << spending << "\n";
	}

}



double calculateDistance(double previousOdometer, double currentOdometer) {
	if (currentOdometer < previousOdometer) {
		cout << "Error: Current odometer reading cannot be less than the previous reading.\n";
		return -1; 
	}
	return currentOdometer - previousOdometer;
}

bool calculateKmPerL(double distance, double liters, double& kmPerL) {
	if (liters <= 0   || distance < 0) {
		kmPerL = 0;
		cout << "Error: Liters and distance must be greater than zero to calculate fuel efficiency.\n";
		return false;
	}
	kmPerL = distance / liters;
	return true;
}


EfficiencyResult calculateVehicleEfficiency(
	const FuelRecord* fuel,
	int fuelCount,
	int vehicleID)
{
	EfficiencyResult result;

	result.vehicleID = vehicleID;
	result.intervals = 0;
	result.distance = 0;
	result.litresUsed = 0;
	result.kmPerL = 0;
	result.valid = false;

	
	int previousFullTank = -1;

	for (int i = 0; i < fuelCount; i++)
	{
		if (fuel[i].vehicleID == vehicleID && fuel[i].fullTank)
		{
			previousFullTank = i;
			break;
		}
	}

	while (previousFullTank != -1)
	{
		int nextFullTank = -1;

		for (int i = previousFullTank + 1; i < fuelCount; i++)
		{
			if (fuel[i].vehicleID == vehicleID && fuel[i].fullTank)
			{
				nextFullTank = i;
				break;
			}
		}

		if (nextFullTank == -1)
		{
			break;
		}

		double distance = calculateDistance(
			fuel[previousFullTank].odometer,
			fuel[nextFullTank].odometer);

		
		double litresUsed = 0;

		for (int i = previousFullTank + 1; i <= nextFullTank; i++)
		{
			if (fuel[i].vehicleID == vehicleID)
			{
				litresUsed += fuel[i].litres;
			}
		}

		if (distance > 0 && litresUsed > 0)
		{
			result.distance += distance;
			result.litresUsed += litresUsed;
			result.intervals++;
		}

		previousFullTank = nextFullTank;
	}

	if (result.intervals > 0 && result.litresUsed > 0)
	{
		result.kmPerL = result.distance / result.litresUsed;
		result.valid = true;
	}

	return result;
}



int loadFuelRecords(FuelRecord* fuel, int fuelCapacity,
	const Vehicle* vehicles, int vehicleCount, int& skipped,
	const string& filename)
{
	skipped = 0;
	ifstream inFile(filename);

	if (!inFile) {
		cout << "Error: Unable to open file: " << filename << "\n";
		return 0;
	}

	FuelRecord record;
	int loaded = 0;

	while (inFile >> record.vehicleID
		>> record.date
		>> record.litres
		>> record.pricePerLitre
		>> record.odometer
		>> record.fullTank)
	{
		if (loaded >= fuelCapacity)
		{
			skipped++;
			continue;
		}

		if (findVehicleIndex(vehicles, vehicleCount, record.vehicleID) == -1)
		{
			skipped++;
			continue;
		}

		string errorMessage;
		if (!validateFuelRecord(record, vehicles, vehicleCount, fuel, loaded, errorMessage))
		{
			skipped++;
			continue;
		}

		fuel[loaded] = record;
		loaded++;
	}

	inFile.close();

	cout << "Fuel records loaded: " << loaded << "\n";
	cout << "Fuel records skipped: " << skipped << "\n";

	return loaded;


}


void calculateAllEfficiencies(
	const Vehicle* vehicles,
	int vehicleCount,
	const FuelRecord* fuel,
	int fuelCount,
	EfficiencyResult* results)
{
	for (int i = 0; i < vehicleCount; i++)
	{
		results[i] = calculateVehicleEfficiency(fuel, fuelCount, vehicles[i].vehicleID);
	}
}


int findMostEfficientVehicle(
	const EfficiencyResult* results,
	int count)
{
	int bestIndex = -1;
	double highestEfficiency = 0;

	for (int i = 0; i < count; i++)
	{
		if (results[i].valid &&
			results[i].kmPerL > highestEfficiency)
		{
			highestEfficiency = results[i].kmPerL;
			bestIndex = i;
		}
	}

	return bestIndex;
}


void displayEfficiencyDetails(
	const Vehicle* vehicles,
	int vehicleCount,
	const FuelRecord* fuel,
	int fuelCount,
	int vehicleID)
{
	int index = findVehicleIndex(vehicles, vehicleCount, vehicleID);

	if (index == -1)
	{
		cout << "Error: Vehicle not found!\n";
		return;
	}

	EfficiencyResult result =
		calculateVehicleEfficiency(fuel, fuelCount, vehicleID);

	cout << "\n===== FUEL EFFICIENCY DETAILS =====\n";
	cout << "Vehicle: " << vehicles[index].name << "\n";
	cout << "Vehicle ID: " << vehicleID << "\n";

	if (!result.valid)
	{
		cout << "Insufficient data for accurate fuel efficiency.\n";
		return;
	}

	cout << "Completed Intervals: " << result.intervals << "\n";
	cout << "Total Distance: " << result.distance << " km\n";
	cout << "Fuel Used: " << result.litresUsed << " litres\n";
	cout << "Fuel Efficiency: " << result.kmPerL << " km/L\n";
}




void displayEfficiencyComparison(
	const Vehicle* vehicles,
	int vehicleCount,
	const FuelRecord* fuel,
	int fuelCount)
{
	if (vehicleCount == 0)
	{
		cout << "No vehicles available!\n";
		return;
	}

	EfficiencyResult results[MAX_VEHICLES];

	calculateAllEfficiencies(
		vehicles, vehicleCount,
		fuel, fuelCount, results);

	cout << "\n========== FUEL EFFICIENCY COMPARISON ==========\n";

	cout << left
		<< setw(12) << "Vehicle ID"
		<< setw(20) << "Vehicle Name"
		<< setw(15) << "Efficiency"
		<< "\n";

	cout << "-------------------------------------------------\n";

	for (int i = 0; i < vehicleCount; i++)
	{
		cout << left
			<< setw(12) << vehicles[i].vehicleID
			<< setw(20) << vehicles[i].name;

		if (results[i].valid)
		{
			cout << fixed << setprecision(2)
				<< results[i].kmPerL << " km/L\n";
		}
		else
		{
			cout << "Insufficient data\n";
		}
	}

	int bestIndex = findMostEfficientVehicle(results, vehicleCount);

	if (bestIndex != -1)
	{
		cout << "\nMost Efficient Vehicle: "
			<< vehicles[bestIndex].name << "\n";

		cout << "Efficiency: "
			<< fixed << setprecision(2)
			<< results[bestIndex].kmPerL << " km/L\n";
	}
	else
	{
		cout << "\nNo vehicle has sufficient efficiency data yet.\n";
	}
}



void displayEfficiencyGraph(
	const Vehicle* vehicles,
	int vehicleCount,
	const FuelRecord* fuel,
	int fuelCount)
{
	if (vehicleCount == 0)
	{
		cout << "No vehicles available!\n";
		return;
	}

	EfficiencyResult results[MAX_VEHICLES];

	calculateAllEfficiencies(
		vehicles, vehicleCount,
		fuel, fuelCount, results);

	cout << "\n========== FUEL EFFICIENCY GRAPH ==========\n";
	cout << "Each # represents approximately 1 km/L\n\n";

	for (int i = 0; i < vehicleCount; i++)
	{
		cout << vehicles[i].name << " | ";

		if (!results[i].valid)
		{
			cout << "Insufficient data\n";
			continue;
		}

		int bars = static_cast<int>(results[i].kmPerL);

		for (int j = 0; j < bars; j++)
		{
			cout << "#";
		}

		cout << " " << fixed << setprecision(2)
			<< results[i].kmPerL << " km/L\n";
	}
}


int getMonthlyFuelSpending(
	const FuelRecord* fuel,
	int fuelCount,
	int vehicleID,
	MonthlySpend* out,
	int maxMonths)

{
	int monthCount = 0;

	for (int i = 0; i < fuelCount; i++) {
	  
		if (vehicleID != ALL_VEHICLES && fuel[i].vehicleID != vehicleID) {
			continue;
		}


		string month = fuel[i].date.substr(0, 7);
		double cost = calculateFuelCost(fuel[i]);

		int foundIndex = -1;

		for (int j = 0; j < monthCount; j++) {
			if (out[j].month == month) {
				foundIndex = j;
				break;
			}
		}


		if (foundIndex != -1) {
			out[foundIndex].total += cost;
		}
		else if (monthCount < maxMonths) {
		
			out[monthCount].month = month;
			out[monthCount].total = cost;
			monthCount++;
		
		
		}
		}
	return monthCount;
	}



void displayMonthlySpendingGraph(
	const Vehicle* vehicles,
	int vehicleCount,
	const FuelRecord* fuel,
	int fuelCount,
	int vehicleID)
{
	if (fuelCount == 0)
	{
		cout << "No fuel records available!\n";
		return;
	}

	MonthlySpend monthlySpending[MAX_RECORDS];

	int monthCount = getMonthlyFuelSpending(
		fuel, fuelCount, vehicleID,
		monthlySpending, MAX_RECORDS);

	if (monthCount == 0)
	{
		cout << "No fuel spending data available!\n";
		return;
	}

	cout << "\n========== MONTHLY FUEL SPENDING ==========\n";
	cout << "Each # represents approximately 100 units of currency.\n\n";

	for (int i = 0; i < monthCount; i++)
	{
		cout << monthlySpending[i].month << " | ";

		int bars = static_cast<int>(
			monthlySpending[i].total / 100);

		for (int j = 0; j < bars; j++)
		{
			cout << "#";
		}

		cout << " " << fixed << setprecision(2)
			<< monthlySpending[i].total << "\n";
	}
}







