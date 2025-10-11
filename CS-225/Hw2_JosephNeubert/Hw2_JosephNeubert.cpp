/****************************************************************************
 * File:     Hw2_JosephNeubert.cpp
 * Author:   Joseph Neubert
 * Purpose:  Use operators, cout, cin, and conditionals for a money struct.
 * Version:  1.0 Sept 6, 2024
 * Resources: N/A
 *******************************************************************************/

#include <iostream>
#include <string>
using namespace std;

struct money
{
    int dollars;
    int cents;
};

int main()
{
    money money1;
    money money2;
    money money3;

    // Money Object 1
    cout << "Money Object 1\nEnter the dollar amount: ";
    cin >> money1.dollars;
    if (!cin || money1.dollars < 0)
    {
        cout << "Invalid amount. Value set to 1." << endl;
        money1.dollars = 1;
    }
    cin.clear();
    cin.ignore(INT_MAX, '\n');

    cout << "Enter cents amount: ";
    cin >> money1.cents;
    if (!cin || money1.cents < 0)
    {
        cout << "Invalid amount. Value set to 1." << endl;
        money1.cents = 1;
    }
    cin.clear();
    cin.ignore(INT_MAX, '\n');

    money1.dollars += money1.cents / 100;
    money1.cents = money1.cents % 100;
    string money1_string("");
    if (money1.cents < 10)
    {
        money1_string = "$" + to_string(money1.dollars) + ".0" + to_string(money1.cents);
    }
    else
    {
        money1_string = "$" + to_string(money1.dollars) + "." + to_string(money1.cents);
    }
    cout << money1_string << endl;

    // Money Object 2
    cout << "\nMoney Object 2\nEnter the dollar amount: ";
    cin >> money2.dollars;
    if (!cin || money2.dollars < 0)
    {
        cout << "Invalid amount. Value set to 1." << endl;
        money2.dollars = 1;
    }
    cin.clear();
    cin.ignore(INT_MAX, '\n');

    cout << "Enter cents amount: ";
    cin >> money2.cents;
    if (!cin || money2.cents < 0)
    {
        cout << "Invalid amount. Value set to 1." << endl;
        money2.cents = 1;
    }
    cin.clear();
    cin.ignore(INT_MAX, '\n');

    money2.dollars += money2.cents / 100;
    money2.cents = money2.cents % 100;
    string money2_string("");
    if (money2.cents < 10)
    {
        money2_string = "$" + to_string(money2.dollars) + ".0" + to_string(money2.cents);
    }
    else
    {
        money2_string = "$" + to_string(money2.dollars) + "." + to_string(money2.cents);
    }
    cout << money2_string << endl;

    // Addition or subtraction of money objects
    int flag;
    string money3_string("");
    cout << "Enter '1' to add the money values, '2' to subtract them: ";
    cin >> flag;
    if (flag == 1)
    {
        int centsBuffer = money1.cents + money2.cents;
        money3.cents = centsBuffer % 100;
        money3.dollars = money1.dollars + money2.dollars + (centsBuffer / 100);

        if (money3.cents < 10)
        {
            money3_string = "$" + to_string(money3.dollars) + ".0" + to_string(money3.cents);
        }
        else
        {
            money3_string = "$" + to_string(money3.dollars) + "." + to_string(money3.cents);
        }

        cout << money1_string << " + " << money2_string << " = " << money3_string << endl;
    }
    else if (flag == 2)
    {
        int centsBuffer = money1.cents - money2.cents;
        money3.cents = centsBuffer % 100;
        money3.dollars = money1.dollars - money2.dollars - (centsBuffer / 100);

        if (money3.cents < 10)
        {
            money3_string = "$" + to_string(money3.dollars) + ".0" + to_string(money3.cents);
        }
        else
        {
            money3_string = "$" + to_string(money3.dollars) + "." + to_string(money3.cents);
        }

        cout << money1_string << " + " << money2_string << " = " << money3_string << endl;
    }
    else
    {
        cout << "Not a valid input." << endl;
    }
    return 0;
}