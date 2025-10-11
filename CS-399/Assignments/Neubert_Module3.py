"""
File: Neubert_Module3.py
Author: Joseph Neubert
Description: Program to create an exponential backoff decorator
"""

from random import randint
from time import sleep, asctime


def backoff(
    initial_delay: float = 0.01,
    back_off_factor: float = 2,
    max_delay: float = float("inf"),
) -> callable:
    def decorator(func: callable):
        delay = 0

        def inner(*args, **kwargs):
            nonlocal delay
            print(
                f"{asctime()}: will be calling {func.__name__} after {delay} sec delay"
            )
            sleep(delay)
            result = func(*args, **kwargs)
            if result is None or result is False:
                if delay == 0:
                    delay = initial_delay
                elif delay >= max_delay:
                    delay = max_delay
                else:
                    delay *= back_off_factor
            else:
                delay = 0
            return result

        return inner

    return decorator


@backoff(initial_delay=0.1, back_off_factor=1.5, max_delay=2.5)
def call_shaky_service():
    return 6 == randint(1, 6)


while True:
    print(call_shaky_service())
