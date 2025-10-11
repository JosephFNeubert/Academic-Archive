def tripled(number: int) -> int:
    return number * 3


numbers = [1, 2, 3, 4]

tripled_numbers = list(map(tripled, numbers))

print(tripled_numbers)
print([3 * x for x in numbers])
