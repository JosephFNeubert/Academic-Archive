"""
File: Neubert_Final.py
Author: Joseph Neubert
Description: A final program of the class that'll implement 3 different functions.
"""


def foo(ints: [int]) -> [int]:
    """Inputs integer list to output the very list in descending order with only unique squares of the even numbers"""
    new_ints = [x**2 for x in ints if x % 2 == 0]
    new_ints_set = set(new_ints)
    return sorted(list(new_ints_set), reverse=True)


def bar(s: str) -> int:
    """Inputs a string to output a count of all vowels within the string (not case-senstive)"""
    count = 0
    s = s.lower()
    for i in s:
        if i == "a" or i == "e" or i == "i" or i == "o" or i == "u":
            count += 1
    return count


def baz(d: {str: int}) -> [str]:
    """Inputs a dictionary of string keys and integer values to output a list of each key that's associated with the value 42"""
    return [x for x, y in d.items() if y == 42]


# Assert Tests Begin
assert foo([2, 3, 5, 2, 3, 8, 2, 3, 4]) == [64, 16, 4]
assert foo([]) == []

assert bar("Hello Universe") == 6  # count of vowels
assert bar("") == 0
assert bar("x") == 0
assert bar("iii") == 3

assert baz({"a": 42, "b": 10, "c": 42, "d": 30}) == ["a", "c"]
assert baz({}) == []
assert baz({"a": 40, "b": 10, "c": 40, "d": 30}) == []
assert baz({"a": 42, "b": 42, "c": 42, "d": 42}) == ["a", "b", "c", "d"]
