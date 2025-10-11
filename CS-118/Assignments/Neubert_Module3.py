"""
File: Neubert_Module3.py
Author: Joseph Neubert
Purpose: This program will take a integer input and output whether it's prime or not. If it's not prime, it'll also output the lowest factor that isn't 1. If the input is less than or equal to 1, the program will not continue to iterate.
"""
while True:
    user_number = input("Please enter a number greater than 1 to see if it is prime: ")
    number = 0
    isPrime = True

    if user_number.isdigit():
        number = int(user_number)
    else:
        break

    if number == 2:
        print("2 is a prime number.")
    elif number > 2:
        for i in range(2, number):
            if number % i == 0:
                print(f"{number} is not prime number because it is divisible by {i}.")
                isPrime = False
                break
        if isPrime == True:
            print(f"{number} is a prime number.")
    else:
        break
