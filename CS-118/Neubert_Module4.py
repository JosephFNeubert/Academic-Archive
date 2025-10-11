"""
File: Neubert_Module4.py
Author: Joseph Neubert
Description: A random integer generator that will fill a list until each unique number in the specified range is present. Then will output some statistics about the list of random integers.
"""
from random import randint

print("Creating all integers from 1 to n (inclusive) randomly.")

while True:
    user_number = input("Please enter a number, or 'q' to quit: ")
    final_number = 0
    num_list = []

    # Decision based off input
    if user_number.isdigit():
        final_number = int(user_number)
        if final_number == 0:
            continue
    elif user_number == "q":
        break
    else:
        continue

    # Create list with randints
    for i in range(1, final_number + 1):
        while i not in num_list:
            num_list.append(randint(1, final_number))

    # Determines the most-occurring integer in a row
    row_current_count = 1
    row_max_count = 1
    row_max_number = num_list[0]
    for i in range(1, len(num_list)):
        if num_list[i] == num_list[i - 1]:
            row_current_count += 1
        else:
            row_current_count = 1

        if row_current_count > row_max_count:
            row_max_count = row_current_count
            row_max_number = num_list[i]

    # Creates a secondary list of only the unique integers of the original list
    new_num_list = []
    for i in range(0, len(num_list)):
        if num_list[i] not in new_num_list:
            new_num_list.append(num_list[i])

    # Prints all results
    print(
        f"Creating a random sequence of all integers 1 .. {final_number} required {len(num_list)} randint(1,{final_number}) calls."
    )
    print(f"The integer that was created last was {num_list[-1]}.")
    print(
        f"The integer that was created the most times in a row, {row_max_count} times, was {row_max_number}."
    )
    print(new_num_list)
