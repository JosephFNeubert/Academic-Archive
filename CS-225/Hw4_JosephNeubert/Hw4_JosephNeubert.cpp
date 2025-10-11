/****************************************************************************
 * File: Hw4_JosephNeubert.cpp
 * Author: Joseph Neubert
 * Purpose: To create a car class
 * Version: 1.0 Sept 20, 2024
 * Resources: N/A
 *******************************************************************************/
#include <iostream>
#include <cstdlib>
#include <string>

using namespace std;

class Car
{
private:
	string make;
	double mpg;
	double fuel;
	double fuelCapacity;
	double odometer;

public:
	void setCar(string = "Ford", double = 30, double = 90, double = 150, double = 1000);
	void showCar();
	void fuelUp(int);
	void drive();
	void drive(int);
};

void Car::setCar(string newMake, double newMpg, double newFuel, double newCapacity, double newOdometer)
{
	// Set make of car
	make = newMake;

	// Set fuel capacity
	if (newCapacity < 0)
	{
		fuelCapacity = 0;
	}
	else
	{
		fuelCapacity = newCapacity;
	}

	// Set fuel
	if (newFuel > fuelCapacity)
	{
		fuel = fuelCapacity;
	}
	else if (newFuel < 0)
	{
		fuel = 0;
	}
	else
	{
		fuel = newFuel;
	}

	// Set MPG
	if (newMpg < 0)
	{
		mpg = 1;
	}
	else
	{
		mpg = newMpg;
	}

	// Set Odometer
	if (newOdometer < 0)
	{
		odometer = 0;
	}
	else
	{
		odometer = newOdometer;
	}
}

void Car::showCar()
{
	cout << "Make: " << make << "\nFuel Tank Capacity: " << fuelCapacity << "\nMiles per Gallon: " << mpg << "\nFuel in Tank: " << fuel << "\nOdometer Reading: " << odometer << endl;
}

void Car::fuelUp(int fillUp)
{
	if (fillUp + fuel > fuelCapacity)
	{
		cout << "You tried to fill the car with more fuel than it can hold and spilled " << fillUp + fuel - fuelCapacity << "gallons." << endl;
		fuel = fuelCapacity;
	}
	else
	{
		fuel += fillUp;
	}
}

void Car::drive()
{
	srand(time(0));
	int randomDistance = (rand() % 100);
	double originalOdometer = odometer;
	double leftoverFuel = 0;

	fuel -= randomDistance / mpg;
	odometer += randomDistance;
	if (fuel < 0)
	{
		leftoverFuel = fuel * (-1);
		fuel = 0;
		odometer -= leftoverFuel * mpg;
	}
	cout << "You decided to go on a " << randomDistance << "-mile joyride. ";
	if (odometer - originalOdometer == randomDistance)
	{
		cout << "You accomplished your journey." << endl;
	}
	else
	{
		cout << "You only managed to travel " << odometer - originalOdometer << " miles before running out of fuel." << endl;
	}
}

void Car::drive(int distance)
{
	double originalOdometer = odometer;
	double leftoverFuel = 0;

	fuel -= distance / mpg;
	odometer += distance;
	if (fuel < 0)
	{
		leftoverFuel = fuel * (-1);
		fuel = 0;
		odometer -= leftoverFuel * mpg;
	}
	if (odometer - originalOdometer == distance)
	{
		cout << "You accomplished your journey." << endl;
	}
	else
	{
		cout << "You only managed to travel " << odometer - originalOdometer << " miles before running out of fuel." << endl;
	}
}

int main()
{
	Car c;
	c.setCar();
	bool flag = true;
	int selection;

	while (flag)
	{
		cout << "************************************************" << endl;
		c.showCar();
		cout << "************************************************" << endl;
		cout << "Select " << endl;
		cout << "1) Go on a joyride\n2) Drive a set distance\n3) Fuel up\n4) Exit" << endl;
		cin >> selection;
		if (selection == 1)
		{
			c.drive();
		}
		else if (selection == 2)
		{
			int x;
			cout << "How many miles do you want to drive: ";
			cin >> x;
			if (!cin || x < 0)
			{
				x = 0;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			c.drive(x);
		}
		else if (selection == 3)
		{
			int x;
			cout << "How many gallons of fuel do you want to put in: ";
			cin >> x;
			if (!cin || x < 0)
			{
				x = 0;
				cin.clear();
				cin.ignore(INT_MAX, '\n');
			}
			c.fuelUp(x);
		}
		else if (selection == 4)
		{
			flag = false;
		}
		else
		{
			cout << "You have selected an incorrect option. Try again." << endl;
			cin.clear();
			cin.ignore(INT_MAX, '\n');
		}
	}
	return 0;
}