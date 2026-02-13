#include <iostream>
class Calculator
{
public:
    // Constructor is implicitly defined
    Calculator() {}

    // method to add two integers
    int add(int a, int b)
    {
        return a + b;
    }

    // method to subtract the second integer from the first
    int subtract(int a, int b)
    {
        return a - b;
    }
    // method to multiply two integers
    int multiply(int a, int b)
    {
        return a * b;
    }
};

// Function to test the add method
void testAddFunction(Calculator &calculator)
{
    struct Test
    {
        int a, b;
        int expected;
        std::string testName;
    };

    Test tests[] = {
        {5, 3, 8, "Test Adding Positive Numbers"},
        {-1, -1, -2, "Test Adding Negative Numbers"},
        {1000, 2000, 3000, "Test Adding Large Numbers"},
        {0, 0, 0, "Test Adding Zeros"},
        {-10, 10, 0, "Test Adding Negative and Positive Numbers"}};

    bool pass = true;
    for (const auto &test : tests)
    {
        int result = calculator.add(test.a, test.b);
        bool testResult = (result == test.expected);
        pass = pass && testResult;
        std::cout << test.testName << " - Expected: " << test.expected << ", Got: " << result
                  << " - " << (testResult ? "PASS" : "FAIL") << std::endl;
    }
    if (pass)
    {
        std::cout << "All add function tests passed!" << std::endl;
    }
    else
    {
        std::cout << "Some add function tests failed!" << std::endl;
    }
}

// Function to test the subtract method
void testSubtractFunction(Calculator &calculator)
{
    struct Test
    {
        int a, b;
        int expected;
        std::string testName;
    };

    Test tests[] = {
        {8, 3, 5, "Test Subtracting Positive Numbers"},
        {-5, -6, 1, "Test Subtracting Negative Numbers and Receiving a Positive Number"},
        {-5000, 1001, -6001, "Test Subtracting Large Numbers"},
        {0, 0, 0, "Test Subtracting Zeros"},
        {10, -5, 15, "Test Subtracting Negative Numbers from Positive Numbers"}};

    bool pass = true;
    for (const auto &test : tests)
    {
        int result = calculator.subtract(test.a, test.b);
        bool testResult = (result == test.expected);
        pass = pass && testResult;
        std::cout << test.testName << " - Expected: " << test.expected << ", Got: " << result
                  << " - " << (testResult ? "PASS" : "FAIL") << std::endl;
    }
    if (pass)
    {
        std::cout << "All add function tests passed!" << std::endl;
    }
    else
    {
        std::cout << "Some add function tests failed!" << std::endl;
    }
}

// Function to test the multiply method
void testMultiplyFunction(Calculator &calculator)
{
    struct Test
    {
        int a, b;
        int expected;
        std::string testName;
    };

    Test tests[] = {
        {5, 3, 15, "Test Multiplying Positive Numbers"},
        {0, 0, 0, "Test Multiplying Zeros"},
        {-1800, 2, -3600, "Test Multiplying Negative and Positive Numbers"},
        {10000, 0, 0, "Test Multiplying by Zero"},
        {120, 360, 43200, "Test Multiplying Large Numbers"}};

    bool pass = true;
    for (const auto &test : tests)
    {
        int result = calculator.multiply(test.a, test.b);
        bool testResult = (result == test.expected);
        pass = pass && testResult;
        std::cout << test.testName << " - Expected: " << test.expected << ", Got: " << result
                  << " - " << (testResult ? "PASS" : "FAIL") << std::endl;
    }
    if (pass)
    {
        std::cout << "All add function tests passed!" << std::endl;
    }
    else
    {
        std::cout << "Some add function tests failed!" << std::endl;
    }
}

// Main
int main()
{
    Calculator calc; // Create an object of Calculator

    // Testing the class functions
    testAddFunction(calc);
    testSubtractFunction(calc);
    testMultiplyFunction(calc);

    return 0;
}