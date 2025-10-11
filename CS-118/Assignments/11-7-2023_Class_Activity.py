def max_of_three(x: int, y: int, z: int) -> int:
    """
    Returns: The max of x, y, and z.
    """
    num_list = [x, y, z]
    max_num = 0
    for i in num_list:
        if i > max_num:
            max_num = i
    return max_num


def multiply(numbers: [int]) -> int:
    """
    Returns: The product of all numbers in the integer list.
    """
    product = 1
    for i in numbers:
        product *= i
    return product


def squared(numbers: [int]) -> [int]:
    """
    Returns: The squared values of each list item
    """
    new_numbers = []
    for i in numbers:
        new_numbers.append(i**2)
    return new_numbers


assert 3 == max_of_three(1, 3, 2)
assert 24 == multiply([1, 2, 3, 4])
assert [1, 4, 9] == squared([1, 2, 3])
