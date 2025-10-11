def r_sum(x: int) -> int:
    """
    Purpose: Calculates a sum recursively
    """
    if x > 1:
        return x + r_sum(x - 1)
    else:
        return 1


def find_even(x: [int]) -> [int]:
    """
    Purpose: To use list comprehension to output a list of only even integers
    """
    return [i for i in x if i % 2 == 0]


assert r_sum(1) == 1
assert r_sum(10) == sum(range(11))
