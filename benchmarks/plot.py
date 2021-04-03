import matplotlib.pyplot as plt
import pandas as pd

data = pd.read_csv("abstraction.csv")

plt.plot(data[data.columns[0]], data[data.columns[1]], label="Template")
plt.plot(data[data.columns[0]], data[data.columns[2]], label="Explicit")
plt.xlabel("BFS Depth")
plt.ylabel("Time (ms)")
plt.title("Template vs. Explicit Implementation")
plt.legend(loc="upper left")
plt.show()
