#include <iostream>
#include <string>

class Calculator
{
public:
    // Constructor is implicitly defined
    Calculator() {}

    // Method to add two integers
    int add(int a, int b)
    {
        return a + b;
    }

    // Method to subtract the second integer from the first
    int subtract(int a, int b)
    {
        return a - b;
    }

    // Method to multiply two integers
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

void testSubtractFunction(Calculator &calculator)
{
    struct Test
    {
        int a, b;
        int expected;
        std::string testName;
    };

    Test tests[] = {
        {5, 3, 2, "Test Subtracting Positive Numbers"},
        {50, -23, 73, "Test Subtracting A Negative Number from a Positive Number"},
        {214783647, -2, 214783649, "Test Subtracting Large Numbers"},
        {-10, -11, 1, "Test Subtracting Negative Numbers"},
        {0, 0, 0, "Test Subtracting Zeros"}};

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
        std::cout << "All subtract function tests passed!" << std::endl;
    }
    else
    {
        std::cout << "Some subtract function tests failed!" << std::endl;
    }
}

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
        {-20, -5, 100, "Test Multipling Negative Numbers"},
        {0, 0, 0, "Test Multiplying Zeros"},
        {5000, 0, 0, "Test Multiplying a Large Number with Zero"},
        {5, -2, -10, "Test Multiplying Two Negative Numbers"}};

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
        std::cout << "All multiply function tests passed!" << std::endl;
    }
    else
    {
        std::cout << "Some multiply function tests failed!" << std::endl;
    }
}

int main()
{
    Calculator calc; // Create an object of Calculator

    // Testing the add function
    testAddFunction(calc);
    testSubtractFunction(calc);
    testMultiplyFunction(calc);

    return 0;
}
