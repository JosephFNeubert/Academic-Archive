/*
 * Author: Joseph Neubert
 * File: Neubert_SE420_Assignment5_Program.cpp
 * Description: This program finds the next day from an input date. The program also includes test cases for software QA that can be read into the program via a test cases text file.
 */

// Constants
const int MIN_YEAR = 1900;
const int MAX_YEAR = 2025;
const std::string TEST_CASES_FILE = "TEST_CASES.txt";

// Imports
#include <iostream>
#include <string>
#include <stdexcept>
#include <exception>
#include <unordered_map>
#include <fstream>
#include <sstream>
#include <vector>

// Hash Maps for Months and their Days
std::unordered_map<std::string, int> days = {
    {"January", 31},
    {"February", 29},
    {"March", 31},
    {"April", 30},
    {"May", 31},
    {"June", 30},
    {"July", 31},
    {"August", 31},
    {"September", 30},
    {"October", 31},
    {"November", 30},
    {"December", 31},
};

std::unordered_map<int, std::string> months = {
    {1, "January"},
    {2, "February"},
    {3, "March"},
    {4, "April"},
    {5, "May"},
    {6, "June"},
    {7, "July"},
    {8, "August"},
    {9, "September"},
    {10, "October"},
    {11, "November"},
    {12, "December"},
};

/* Support Functions for Next-Date Function */
// Function to check if the input year is a leap year
bool isLeapYear(int year)
{
    bool leapYear = false;
    if (year % 4)
    {
        leapYear = true;
    }

    if (year % 100 == 0)
    {
        leapYear = false;
        if (year % 400 == 0)
        {
            leapYear = true;
        }
    }

    return leapYear;
}

// Function to check if the input day is valid for the month
bool isDayValid(int day, int month)
{
    if (day > days[months[month]] || day <= 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Function to check if the input month is valid and within range
bool isMonthValid(int month)
{
    if (months.count(month) == 0)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Function to check if the input year is valid and within the prescribed range
bool isYearValid(int year)
{
    if (year > MAX_YEAR || year < MIN_YEAR)
    {
        return false;
    }
    else
    {
        return true;
    }
}

// Function to convert a date composed of input integers into a string date representation
std::string ConvertDateToString(int day, int month, int year)
{
    std::string nextDateDayStr = std::to_string(day);
    std::string nextDateMonthStr = std::to_string(month);
    std::string nextDateYearStr = std::to_string(year);

    if (nextDateDayStr.length() == 1)
    {
        nextDateDayStr = "0" + nextDateDayStr;
    }
    if (nextDateMonthStr.length() == 1)
    {
        nextDateMonthStr = "0" + nextDateMonthStr;
    }

    return nextDateMonthStr + "_" + nextDateDayStr + "_" + nextDateYearStr;
}

// Function to print a date string into a standard, more digestible MMDDYY
// void PrintDateString(std::string date)

/* Next-Date Function */
std::string NextDate(int day, int month, int year)
{
    // Phase 1: Catch Invalid Inputs
    try
    {
        if (!isDayValid(day, month))
        {
            throw std::invalid_argument("Invalid Input Date");
        }
        if (!isMonthValid(month))
        {
            throw std::invalid_argument("Value of Month Not in the Range of 1...12");
        }
        if (!isYearValid(year))
        {
            throw std::invalid_argument("Year Not Between Range of 1900-2025");
        }
        if (!isLeapYear(year) && month == 2 && day == 29)
        {
            throw std::invalid_argument("Not a Leap Year");
        }
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
    }

    // Phase 2: Handling for Non-Leap Years
    if (!isLeapYear(year) && month == 2 && day == 28)
    {
        return "03_01_" + std::to_string(year);
    }

    // Phase 3: No Special Conditions; Simple Calculation of the Next Date
    int nextDateDay;
    int nextDateMonth;
    int nextDateYear;

    if (month == 12)
    {
        nextDateYear = year++;
        nextDateMonth = 1;
        nextDateDay = 1;
    }
    else if (day == days[months[month]])
    {
        nextDateMonth = month++;
        nextDateDay = 1;
        nextDateYear = year;
    }
    else
    {
        nextDateDay = day++;
        nextDateMonth = month;
        nextDateYear = year;
    }

    return ConvertDateToString(nextDateDay, nextDateMonth, nextDateYear);
}

/* Functions for Creating and Reading Test Cases for this Program */
// Function to create a new test case
void WriteNewTestCase(std::string testCase, std::string filePath)
{
    std::ofstream File(filePath);
    File << testCase << std::endl;
    File.close();
}

// Function to read all test cases to a string vector
std::vector<std::string> ReadTestCases(std::string filePath)
{
    std::vector<std::string> testCases;
    std::ifstream File(filePath);
    std::string line;

    while (std::getline(File, line))
    {
        testCases.push_back(line);
    }

    File.close();
    return testCases;
}

// Function to run a test case
void RunTestCase(std::string testCase)
{
    std::stringstream ss(testCase);
    std::string element;
    std::vector<std::string> elements;

    while (std::getline(ss, element, '_'))
    {
        elements.push_back(element);
    }

    int month = std::stoi(elements.at(0));
    int day = std::stoi(elements.at(1));
    int year = std::stoi(elements.at(2));

    std::cout << NextDate(day, month, year) << std::endl;
}

// Main
int main()
{
    std::cout << "Next Date Program!" << std::endl;
    bool flag = true;
    std::string input;
    do
    {
        std::cout << "Type '1' to add a new test case, type '2' to run all test cases." << std::endl;
        std::cin >> input;
        if (input.compare("2") == 0)
        {
            flag = false;
        }
        else if (input.compare("1") == 0)
        {
            std::string testCase;
            std::cout << "Type in the date to test in the MM_DD_YYYY format (e.g. 02_14_1972 for Feb. 14, 1972)." << std::endl;
            std::cin >> testCase;
            WriteNewTestCase(testCase, TEST_CASES_FILE);
        }
        else
        {
            std::cout << "Not a valid option. Try again." << std::endl;
        }
    } while (flag);

    std::vector<std::string> testCases = ReadTestCases(TEST_CASES_FILE);
    for (int i = 0; i < testCases.size(); i++)
    {
        RunTestCase(testCases.at(i));
    }

    return 0;
}