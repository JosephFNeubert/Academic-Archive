/****************************************************************************
 * File: Hw5_JosephNeubert.cpp
 * Author: Joseph Neubert
 * Purpose: To create a fraction class that creates, multiplies, and displays fractions
 * Version: 1.0 Sept 27, 2024
 * Resources: N/A
 *******************************************************************************/
#include <iostream>

using namespace std;

class Fraction
{
private:
	int wholeNum;
	int numerator;
	int denominator;
	void reduce();

public:
	Fraction();
	Fraction(int, int);
	Fraction(int, int, int);
	int getWholeNum() const;
	int getNumerator() const;
	int getDenominator() const;
	void display(const Fraction &) const;
	Fraction multiply(const Fraction &, const Fraction &) const;
};

Fraction::Fraction()
{
	cout << "To create a fraction, first input the whole number: ";
	cin >> wholeNum;
	while (!cin)
	{
		cout << "ERROR" << endl;
		cout << "To create a fraction, first input the whole number: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> wholeNum;
	}

	cout << "Input the numerator: ";
	cin >> numerator;
	while (!cin)
	{
		cout << "ERROR" << endl;
		cout << "Input the numerator: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> numerator;
	}

	cout << "Input the denominator: ";
	cin >> denominator;
	while (!cin)
	{
		cout << "ERROR" << endl;
		cout << "Input the denominator: ";
		cin.clear();
		cin.ignore(INT_MAX, '\n');
		cin >> denominator;
	}
	if (denominator <= 0)
	{
		denominator = 1;
		cout << "Denominator of 0 is not valid. Changed to 1." << endl;
	}
}

Fraction::Fraction(int numerator, int denominator)
{
	wholeNum = 0;
	this->numerator = numerator;
	if (denominator == 0)
		this->denominator = 1;
	else
		this->denominator = denominator;
}

Fraction::Fraction(int wholeNum, int numerator, int denominator)
{
	this->wholeNum = wholeNum;
	this->numerator = numerator;
	if (denominator == 0)
		this->denominator = 1;
	else
		this->denominator = denominator;
}

int Fraction::getWholeNum() const
{
	return wholeNum;
}

int Fraction::getNumerator() const
{
	return numerator;
}

int Fraction::getDenominator() const
{
	return denominator;
}

void Fraction::display(const Fraction &f) const
{
	Fraction ff = f;
	ff.reduce();
	if (ff.getWholeNum() != 0)
		cout << ff.getWholeNum() << " ";
	if (ff.getNumerator() == ff.getDenominator())
		cout << 1 + f.getWholeNum();
	if (ff.getNumerator() != 0)
		cout << ff.getNumerator() << "/" << ff.getDenominator();
}

void Fraction::reduce()
{
	wholeNum += numerator / denominator;
	numerator %= denominator;
	int staticDenominator = denominator;
	int divisor = 1;
	for (int i = 1; i < staticDenominator; i++)
	{
		if (numerator % i == 0 && denominator % i == 0)
		{
			divisor = i;
		}
	}
	numerator /= divisor;
	denominator /= divisor;
}

Fraction Fraction::multiply(const Fraction &f1, const Fraction &f2) const
{
	int numeratorBuffer = ((f1.getDenominator() * f1.getWholeNum() + f1.getNumerator()) * (f2.getDenominator() * f2.getWholeNum() + f2.getNumerator()));
	int denominatorBuffer = f1.getDenominator() * f2.getDenominator();

	Fraction f(numeratorBuffer, denominatorBuffer);
	f.reduce();
	return f;
}

int main()
{
	cout << "Fraction 1:" << endl;
	Fraction f1;
	cout << "\nFraction 2:" << endl;
	Fraction f2;
	Fraction f3 = f3.multiply(f1, f2);

	f1.display(f1);
	cout << " * ";
	f2.display(f2);
	cout << " = ";
	f3.display(f3);
	return 0;
}