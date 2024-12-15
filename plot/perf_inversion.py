import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

data = pd.read_csv("data/inv.csv", header=None, names=["Type", "Size", "Time"])
grouped = data.groupby("Type")

colors = {"LU": "red", "SN": "blue", "SS": "green"}
labels = {"LU": "LU", "SN": "Naive Multiplication", "SS": "Strassen Multiplication"}

for type, timings in grouped:
    plt.scatter(timings["Size"], timings["Time"], color=colors[type], label=labels[type])

plt.xlabel("Size of matrices")
plt.ylabel("Time")
plt.legend()

plt.show()