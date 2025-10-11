"""
File: Neubert_Module6.py
Author: Joseph Neubert
Description: A program of two functions to find a mode and to perform a reverse lookup in a dictionary respectively.
"""


def mode(numbers: [int]) -> tuple[int]:
    """Returns the mode in a tuple of a list of integers"""
    mode_dict = {}
    mode_list = []

    for i in numbers:
        if i not in mode_dict:
            mode_dict.update({i: 1})
        else:
            mode_dict.update({i: mode_dict.get(i) + 1})
    mode_frequency = max(list(mode_dict.values()))

    return rev_lookup(mode_dict, mode_frequency)


def rev_lookup(d: dict[int, int], v: int) -> tuple[int]:
    """Returns a tuple of the keys whose values match an integer value"""
    lookup_results = []

    for key, value in d.items():
        if value == v:
            lookup_results.append(key)

    return tuple(lookup_results)


print(mode([1, 2, 2, 3]))
print(mode([1, 2, 2, 3, 3]))
print(rev_lookup({1: 2, 2: 1, 3: 2, 4: 1}, 2))
print(rev_lookup({1: 2, 2: 2, 3: 2, 4: 2}, 2))
