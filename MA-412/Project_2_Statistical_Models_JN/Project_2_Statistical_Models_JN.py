"""
File: Project_2_Statistical_Models_JN.py
Author: Joseph Neubert
Description: MA-412 Project 2 Plots for projects part F3.
"""

### SET-UP FOR MODELS ###
# Imports
import numpy as np
import matplotlib.pyplot as plt
from scipy.stats import norm

# Parameters
mu = 8
sigma = 2
Nsim = 10000
n_values = [10, 30, 60]

# Threshold
thresholds = {10: 80, 30: 240, 60: 480}

# Generate graph for each threshold
for n in n_values:
    # Simulate Sn
    X = np.random.normal(mu, sigma, (Nsim, n))
    S_n = X.sum(axis=1)

    # Theoretical Parameters
    mean = n * mu
    std = np.sqrt(n) * sigma

    # Plot
    plt.figure()
    plt.hist(S_n, bins=50, density=True, alpha=0.6, label="Simulated")

    # Overlay normal curve
    x = np.linspace(min(S_n), max(S_n), 1000)
    plt.plot(x, norm.pdf(x, mean, std), "r", lw=2, label="Normal Approx")

    # Labels
    plt.title(f"Distribution of S{n}")
    plt.xlabel("Total inspection time (minutes)")
    plt.ylabel("Density")

    # Empirical probability
    a = thresholds[n]
    prob_emp = np.mean(S_n > a)
    prob_clt = 1 - norm.cdf((a - mean) / std)

    print(f"n={n}")
    print(f"Empirical P(S_n > {a}) = {prob_emp:.4f}")
    print(f"CLT approx             = {prob_clt:.4f}")
    print()

    plt.show()
