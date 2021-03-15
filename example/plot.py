import pandas as pd
from matplotlib import pyplot as plt

df = pd.read_csv("projectile_45_deg.csv", sep=r"\s+")

fig, ax = plt.subplots(figsize=(10, 6))

ax.plot(df["x"], df["y"], "green")
ax.set_xlabel("x")
ax.set_ylabel("y")

# ax2 = ax.twinx()
# ax2.plot(df["x"], df["l"], "blue")
# ax2.set_ylabel("l")

plt.show()
