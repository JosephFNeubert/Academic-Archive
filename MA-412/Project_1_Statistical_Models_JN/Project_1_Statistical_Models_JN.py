"""
File: Project_1_Statistical_Models_JN.py
Author: Joseph Neubert
Description: MA-412 Project 1 Plots for projects parts A - D where n = 2.
"""

### SET-UP FOR MODELS ###
# Imports
import numpy as np
import matplotlib.pyplot as plt
import math

# print(np.__version__)

# Starter Values
p = 0.05
n = 2
q = 1 - p

### PART A ###
# Create a PMF Graph
Px2_1 = q**2
Px2_3 = 1 - Px2_1
x1 = np.array([1, 3])
y1 = np.array([Px2_1, Px2_3])
plt.bar(x1, y1)
plt.xlabel("X")
plt.ylabel("P(X₂ = x)")
plt.title("PMF of X₂ (p = 0.05)")
plt.xticks(range(0, 4))
plt.yticks(np.arange(0, 1.2, 0.2))
plt.show()

### PART B ###
# Calculate Variance and Standard Deviation
var = (1 * (q**2) + (3**2) * (1 - (q**2))) - ((1 * (q**2) + 3 * (1 - (q**2))) ** 2)
stddev = math.sqrt(var)
print(f"Variance: {var}\n")
print(f"Standard Deviation: {stddev}\n")

# Create a CDF Graph
x2 = np.array([0, 1, 1, 3, 3, 4])
y2 = np.array([0, 0, Px2_1, Px2_1, 1, 1])
plt.plot(x2, y2)
plt.xlabel("X")
plt.ylabel("Fxₙ(x)")
plt.title("CDF of X₂ (p = 0.05)")
plt.xticks(range(0, 5))
plt.yticks(np.arange(0, 1.2, 0.2))
plt.show()
