"""
CEC-470 Assignment 4
Author: Joseph Neubert
Description: System endianness (LE) demonstration with my PC.
"""

import sys

# Determine System Endianness
if sys.byteorder == "big":
    print("Big Endian")
elif sys.byteorder == "little":
    print("Little Endian")
else:
    print("Unknown")

# Demonstrate System Endianness with a String
testString = "CEC470"
charList = []
for i in testString:
    x = hex(ord(i))
    charList.insert(0, x)
    print(f"{x} - {i}")

stringList = str(charList)
print(stringList)
