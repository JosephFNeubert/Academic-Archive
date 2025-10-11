"""
File: Neubert_Midterm.py
Author: Joseph Neubert
Description: A program that outputs the answers to 3 questions relating to 77 numbers.
"""
numberlist77 = []
for i in range(1, 78):
    numberlist77.append(i * 77)

# Question 1
print("1. Is 6006 a 77 number?")
if 6006 % 77 == 0 and 6006 / 77 <= 77:
    print("Yes.")
else:
    print("No.")

# Question 2
print("2. What is the sum of all 77 numbers?")
print(f"The sum is {sum(numberlist77)}.")

# Question 3
print("3. What is the 33rd 77 number?")
print(f"The 33rd 77 number is {numberlist77[32]}.")

# Extra Credit Problem
print("Extra Credit: Print the 77 Numbers in reverse order.")
print(numberlist77[::-1])
