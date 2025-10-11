"""
Author: Joseph Neubert
Purpose: This program accepts the height and base length of a square-base pyramid as inputs in order to output the volume and surface 
area.
"""

import math

a = float(input("Pyramid base length: "))
height = float(input("Pyramid height: "))
slant_height = math.sqrt(((a**2) / 4) + height**2)

volume = (1 / 3) * (a**2) * height
surface_area = (a**2) + (2 * a * slant_height)

print(
    f"The pyramid's volume is {volume}.\nThe pyramid's surface area is {surface_area}."
)
