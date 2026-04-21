// Joseph Neubert - Debug Demo
#include <cassert>
#include <iostream>
#include <vector>

int divide(int a, int b) {
	assert(b != 0 && "B cannot be equal to zero"); // Fixed runtime error
	return a / b;
}

int buggy_sum() {
	int sum = 0;
	for (int i = 1; i <= 5; i++) {
		sum += i; // Logic bug fixed with squiggly brackets
	}
	return sum;
}

int read_array() {
	int arr[3] = { 1, 2, 3 };
	int total = 0;
	for (int i = 0; i < 3; i++) { // Equal sign removed to fix logic bug with iterations
		total += arr[i];
	}
	return total;
}

// Memory bugged fixed by using a local variable instead of a pointer
int memory_bug() {
	int p = 5; 
	p = 10;
	return p;
}

// Function refactored for better maintainability
int calc(int a) {
	int step1 = a * a;
	int step2 = 2 * a;
	int step3 = step1 + step2 + 1;
	return step3;
}

// Logs added
int main() {
	int x = 5;
	std::cout << "[log] x = " << x << std::endl;
	int y = x * 2;
	std::cout << "[log] y = " << y << std::endl;
	std::cout << "divide: " << divide(x, y) << "\n";
	int z = y - 10;
	std::cout << "[log] z = " << z << std::endl;
	std::cout << "uninitialized z = " << z << "\n";
	std::cout << "sum = " << buggy_sum() << "\n";
	std::cout << "array total = " << read_array() << "\n";
	std::cout << "memory result = " << memory_bug() << "\n";
	std::cout << "calc(5) = " << calc(5) << "\n";
}