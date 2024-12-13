import pandas as pd
import matplotlib.pyplot as plt
import numpy as np

data = pd.read_csv("data/mult.csv", header=None, names=["Type", "Size", "Time"])
grouped = data.groupby("Type")

colors = {"N": "red", "S": "blue"}
labels = {"N": "Naive", "S": "Strassen"}

for type, timings in grouped:
    plt.scatter(timings["Size"], timings["Time"], color=colors[type], label=labels[type])

# perform some regression too

plt.xlabel("Size of matrices")
plt.ylabel("Time")
plt.legend()

plt.show()