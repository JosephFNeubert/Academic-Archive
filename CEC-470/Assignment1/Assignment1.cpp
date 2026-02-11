/*
 * CEC-470 Assignment 1
 * Author: Joseph Neubert
 * Description: The C++ script to go alongside assignment 1 that demonstrates the difference between serial and parallel computing via the Threads module.
 */

// Imports
#include <iostream>
#include <chrono>
#include <thread>
#include <vector>

// Namespaces
using namespace std;
using namespace std::chrono;

// Function Prototypes
long long add_function(long maxNum);
void half_add_function();

// Constants
const long number = 1500000;

// Main
int main()
{
    /* PART A*/
    // PART A-1
    auto startTime1 = high_resolution_clock::now();
    long long sum1 = add_function(number);
    auto endTime1 = high_resolution_clock::now();
    auto duration1 = duration_cast<milliseconds>(endTime1 - startTime1);
    cout << "SUM: " << sum1 << ", DURATION: " << duration1.count() << "ms" << endl;

    // PART A-2
    auto startTime2 = high_resolution_clock::now();
    for (int i = 0; i < 500; i++)
    {
        sum1 = add_function(number);
    }
    auto endTime2 = high_resolution_clock::now();
    auto duration2 = duration_cast<milliseconds>(endTime2 - startTime2);
    cout << "DURATION OF 500 EXECUTIONS: " << duration2.count() << "ms" << endl
         << endl;

    /*PART B*/
    // PART B-1
    auto startTime3 = high_resolution_clock::now();
    thread t(half_add_function);
    sum1 = add_function(number / 2);
    t.join();
    auto endTime3 = high_resolution_clock::now();
    auto duration3 = duration_cast<milliseconds>(endTime3 - startTime3);
    cout << "DURATION: " << duration3.count() << "ms" << endl;

    // PART B-2
    auto startTime4 = high_resolution_clock::now();
    for (int i = 0; i < 500; i++)
    {
        thread t(half_add_function);
        sum1 = add_function(number / 2);
        t.join();
    }
    auto endTime4 = high_resolution_clock::now();
    auto duration4 = duration_cast<milliseconds>(endTime4 - startTime4);
    cout << "DURATION OF 500 EXECUTIONS: " << duration4.count() << "ms" << endl
         << endl;

    return 0;
}

// Function Definitions
long long add_function(long maxNum)
{
    long long sum = 0;
    for (long i = 0; i < maxNum; i++)
    {
        sum += i;
    }
    return sum;
}

void half_add_function()
{
    long long sum = 0;
    for (long i = (1500000 / 2); i < 1500000; i++)
    {
        sum += i;
    }
}