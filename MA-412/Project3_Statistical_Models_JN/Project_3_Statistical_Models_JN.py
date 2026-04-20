"""
File: Project_3_Statistical_Models_JN.py
Author: Joseph Neubert
Description: MA-412 Project 3 Plot of Linear Regression of a Simulated Returns Excel Dataset and Paired T-tests for P-value
"""

### SET-UP FOR MODELS ###
# Imports
import numpy as np
import pandas as pd
from sklearn.model_selection import train_test_split
from sklearn.linear_model import LinearRegression
from sklearn.metrics import mean_squared_error
import matplotlib.pyplot as plt
import math

# Read Excel dataset as a dataframe
df = pd.read_excel("simulated_returns.xlsx")

# Define independent/dependent variables
x = pd.DataFrame({"x": df.index + 1})
y = df[["Dataset1"]]

# Data split into training and testing sets (80% train, 20% test)
x_train, x_test, y_train, y_test = train_test_split(
    x, y, test_size=0.2, random_state=42
)

# Create linear regression model
model = LinearRegression()
model.fit(x_train, y_train)
y_pred = model.predict(x_test)

# Plot linear regression
plt.scatter(x_test, y_test, color="blue", label="Test Data")
plt.plot(x_test, y_pred, color="red", label="Regression Line")
plt.xlabel("X")
plt.ylabel("Y")
plt.title("Linear Regression Model for Dataset 1")
plt.legend()
plt.show()

# Calculate slope of linear regression
slope = model.coef_[0][0]
print(f"Slope of Linear Regression: {slope}")

# Calculate mean squared error (MSE)
mse = mean_squared_error(y_test, y_pred)
print(f"Mean Square Error: {mse}")

# Paired T-test for datasets 2 and 3 to find P-value
print("")
differences = []
strategy1 = df[["Dataset2"]]
strategy2 = df[["Dataset3"]]
for i in x.index:
    differences.append(strategy1.loc[i, "Dataset2"] - strategy2.loc[i, "Dataset3"])
differences_mean = np.mean(differences)
differences_std = np.std(differences)
n = len(x)
t = differences_mean / (differences_std / math.sqrt(n))
print(f"Mean of Differences: {differences_mean}")
print(f"STD of Differences: {differences_std}")
print(f"n: {n}")
print(f"Calculated T-statistic: {t}")
print(
    f"With {n - 1} degrees of freedom and the above T-statistic, the P-value is 0.50238."
)
