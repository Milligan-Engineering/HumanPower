//File Name: main.cpp
//Author: Casey Williams
//Email Address: cjwilliams@my.milligan.edu
//Assignment: Project Milestone #05
//Description: Program that performs calculations on user inputed electrical data.
//Last Changed: February 12, 2018

#include <iostream>
#include <string>
using namespace std;

bool validateInput(bool bVoltageOrCurrent, double testInput, int dataIndex);

const int DATA_POINTS = 5;
const bool VOLTAGE = true;
const bool CURRENT = false;

double g_voltages[DATA_POINTS];
double g_currents[DATA_POINTS];

int main()
{
	string dataSetName;
	int dataIndex = 0;
	double testVoltage;
	bool bValidInput;
	double testCurrent;
	char menuOption;
	bool bInstantaneousPowers = false;
	bool bAveragePower = false;
	double powers[DATA_POINTS];
	double averagePower = 0;
	char exitLetter;

	cout << "Enter a title for this data set (no spaces): ";
	cin >> dataSetName;

	cout << endl << "Data set uses " << DATA_POINTS << " pairs of voltage/current values.\n";
	do
	{
		cout << endl << "Enter voltage #" << (dataIndex + 1) << " (in volts): ";
		cin >> testVoltage;

		bValidInput = validateInput(VOLTAGE, testVoltage, dataIndex);
		if (bValidInput)
		{
			cout << "Enter current #" << (dataIndex + 1) << " (in amps): ";
			cin >> testCurrent;

			bValidInput = validateInput(CURRENT, testCurrent, dataIndex);
			if (bValidInput)
			{
				dataIndex++;
			}
			else
			{
				cout << "Current is invalid. Re-enter voltage/current pair #" << (dataIndex + 1) << endl;
			}
		}
		else
		{
			cout << "Voltage is invalid. Re-enter voltage/current pair #" << (dataIndex + 1) << endl;
		}
	} while (dataIndex < DATA_POINTS);

	do
	{
		cout << endl << "A: Display instantaneous powers only.\n";
		cout << "B: Display average powers only.\n";
		cout << "C: Display instantaneous and average powers.\n";
		cout << "Please select an option from the menu: ";
		cin >> menuOption;
		switch (menuOption)
		{
		case 'A':
		case 'a':
			bInstantaneousPowers = true;
			break;
		case 'B':
		case 'b':
			bAveragePower = true;
			break;
		case 'C':
		case 'c':
			bInstantaneousPowers = true;
			bAveragePower = true;
			break;
		default:
			cout << endl << "That is not a valid menu option.\n";
		}
	} while (!bInstantaneousPowers && !bAveragePower);

	cout << endl << "For data set '" << dataSetName << "'...\n";

	cout << "Voltages are: ";
	for (int i = 0; i < DATA_POINTS; i++)
	{
		if (i != 0)
		{
			cout << ", ";
		}
		cout << g_voltages[i] << "V";
	}
	cout << endl;

	cout << "Currents are: ";
	for (int i = 0; i < DATA_POINTS; i++)
	{
		if (i != 0)
		{
			cout << ", ";
		}
		cout << g_currents[i] << "A";
	}

	for (int i = 0; i < DATA_POINTS; i++)
	{
		powers[i] = g_voltages[i] * g_currents[i]; // P = VI
		if (bInstantaneousPowers) //only print instantaneous powers if requested, otherwise calcuate them only
		{
			if (i == 0)
			{
				cout << endl << "Instantaneous powers are: ";
			}
			else
			{
				cout << ", ";
			}
			cout << powers[i] << "W";
		}
	}

	if (bAveragePower)
	{
		for (int i = 0; i < DATA_POINTS; i++)
		{
			averagePower += powers[i]; //first sum all the instantaneous powers
		}
		averagePower /= DATA_POINTS; //then divide by the number of data points to get the average power
		cout << endl << "Average power is: " << averagePower << "W";
	}

	cout << endl << endl << "Type a letter to exit: ";
	cin >> exitLetter;

	return 0;
}

bool validateInput(bool bVoltageOrCurrent, double testInput, int dataIndex)
{
	if (testInput >= 0)
	{
		if (bVoltageOrCurrent == VOLTAGE)
		{
			g_voltages[dataIndex] = testInput;

			return true;
		}
		else if (bVoltageOrCurrent == CURRENT)
		{
			g_currents[dataIndex] = testInput;

			return true;
		}
	}
	
	return false;
}