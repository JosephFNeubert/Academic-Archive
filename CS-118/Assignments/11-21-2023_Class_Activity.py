# Example of an inefficient function
def fibonacci(n: int) -> int:
    """Returns the n-th Fibonacci number"""
    print(f"func was called with {n}")
    if n <= 1:
        return 1
    return fibonacci(n - 1) + fibonacci(n - 2)


# print(fibonacci(50))


# Problem 1
from typing import Union
from random import randint


def find(numbers: list[int], n: int) -> Union[int, None]:
    """Return the index if it exists of a number to be found in a list (without using list methods)"""
    index = 0
    for i in numbers:
        if i == n:
            return index
        else:
            index += 1
    return None


print(find([1, 2, 3, 4, 5, 1, 2], 2))
# A binary search algorithm would be more efficient overall


# Problem 2 (Unfinished and not debugged due to limited class time)
v = [2, 5, 2, 4, 9, 4, 7, 1, 0, 7, 8]


def bubble_sort(v: list[int]) -> list[int]:
    """Bubble sorting algorithm"""
    for i in range(len(v) - 1, 0, -1):
        if v[i] < v[i - 1]:
            v[i], v[i - 1] = v[i - 1], v[i]
    if len(v) <= 2:
        return v
    else:
        return v[0] + bubble_sort(v[1:])


print(bubble_sort(v))
