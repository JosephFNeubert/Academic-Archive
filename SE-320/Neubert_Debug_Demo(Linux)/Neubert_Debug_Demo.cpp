// Assignment 5 Code for Debugging and Refactoring - Joseph Neubert

// Imports
#include <cassert>
#include <iostream>
#include <vector>

// Functions for Debugging
int divide(int a, int b) 
  {
    assert(b != 0 && "Assertion that b cannot be 0"); // Input validation preventing division by zero
    if (b == 0) 
    {
      std::cerr << "Cannot divide by zero!" << std::endl;
      return 1;
    }
    return a / b;
  }

int buggy_sum() 
  {
    int sum = 0;
    for (int i = 1; i <= 5; i++) // Semi-colon removed to eliminate logic bug
    {
      sum += i;
    }
    
    return sum;
  }

int read_array() 
  {
    int arr[3] = {1, 2, 3};
    int total = 0;
    for (int i = 0; i < 3; i++) // For loop corrected (replaced <= with <) to prevent out-of-bounds error
    {
      total += arr[i];
    }
  return total;
  }

int memory_bug() 
  {
    int* p = new int(5);
    *p = 10;
    int p_value = *p;
    delete p; // Moved the pointer deletion until after the pointer is no longer necessary to prevent memory bug
    return p_value;
  }
  
int calc(int a) 
  {
    int step1 = a * a;
    int step2 = 2 * a;
    int step3 = step1 + step2;
    int step4 = step3 + 1;
    return step4; // For clarity and better maintainability, this function was refactored into different steps instead of one long equation
  }

// Main Function
// Logs added to track function execution in Main
int main() 
  {
    int x = 5;
    std::cout << "[log] x = " << x << std::endl;
    int y = x * 2;
    std::cout << "[log] y = " << y << std::endl;
    std::cout << "divide: " << divide(x, y) << "\n";
    int z = y - 10;
    std:: cout << "[log] z = " << z << std::endl;
    std::cout << "uninitialized z = " << z << "\n";
    std::cout << "sum = " << buggy_sum() << "\n";
    std::cout << "array total = " << read_array() << "\n";
    std::cout << "memory result = " << memory_bug() << "\n";
    std::cout << "calc(5) = " << calc(5) << "\n";
  }