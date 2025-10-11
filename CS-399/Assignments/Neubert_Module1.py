"""
File: Neubert_Module1.py
Author: Joseph Neubert
Description: An attempt at a highly optimized generator to create prime functions.
"""
import itertools


def prime_number_generator():
    yield 2
    prime_cache = [2]

    for x in itertools.count(3, 2):
        is_prime = True
        for i in list(filter(lambda t: t ** (1 / 2) <= x, prime_cache)):
            if x % i == 0:
                is_prime = False
                break

        if is_prime:
            prime_cache.append(x)
            yield x


# For testing
for i in prime_number_generator():
    print(i)
    if i > 100:
        break
