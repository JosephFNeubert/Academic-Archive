"""
File: Neubert_ex33.py
Author: Joseph Neubert
Description: A showcase of while loops that'll create a list from 0 to 5.
"""
i = 0
numbers = []

while i < 6:
    print(f"At the top i is {i}")
    numbers.append(i)

    i = i + 1
    print(f"Numbers now: {numbers}")
    print(f"At the bottom i is {i}")

print("The numbers: ")
for i in numbers:
    print(i)
