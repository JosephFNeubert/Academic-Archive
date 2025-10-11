"""
File: CS399_Final_Neubert.py
Author: Joseph Neubert
Purpose: Program that endlessly rolls a die and records the results to detect and log potential fraud
"""

from random import randint
from time import sleep
import logging

logging.basicConfig(
    filename="app.log",
    level=logging.DEBUG,
    filemode="w",
    format="%(name)s - %(levelname)s - %(message)s",
)


def fraud_detection(k: int) -> callable:
    """returns a closure that detects fraud in the dice game
    k: the length of the buffer to store the last rolls
    Returns: a closure that takes the current roll as an argument
    and returns a list containing the last k rolls, if fraud is detected otherwise an empty list
    """
    buffer = [0] * k

    def inner(current_roll: int) -> list[int]:
        buffer.append(current_roll)
        buffer.pop(0)
        odd_rolls = [roll for roll in buffer if roll % 2 != 0]
        if len(odd_rolls) == k:
            return odd_rolls
        return []

    return inner


def log_with_trigger(trigger: callable) -> callable:
    def decorator(func):
        def wrapper(*args, **kwargs):
            result = func(*args, **kwargs)
            fraud = trigger(result)
            if fraud:
                logging.warning(f"Fraud detected: {fraud}")
            return result

        return wrapper

    return decorator


@log_with_trigger(trigger=fraud_detection(6))
def roll_the_dice() -> int:
    """Returns a random number between 1 and 6"""
    return randint(1, 6)


if __name__ == "__main__":
    the_sum = 0
    num_of_roll = 0
    while True:
        the_sum += roll_the_dice()
        num_of_roll += 1
        print(
            f"> {num_of_roll}, the average roll is {the_sum/num_of_roll:.3f}", end="\r"
        )
        sleep(0.1)
