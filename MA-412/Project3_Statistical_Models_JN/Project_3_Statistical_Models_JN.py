"""
File: Project_3_Statistical_Models_JN.py
Author: Joseph Neubert
Description: MA-412 Project 3 Plots TODO
"""

### SET-UP FOR MODELS ###
# Imports
import numpy as np
import pandas as pd

import matplotlib.pyplot as plt

df = pd.read_excel("simulated_returns.xlsx")

df = df.drop(columns=["Dataset2", "Dataset3"])
print(df)
