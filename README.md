Development friendly CSV writer
===============================

A CSV file writer that makes it easy to keep track what is in which column
and plot the data in Python with pandas.

Why
---

I develop materials science models in C++, and visualize the results in Python.
During development I frequently need to add new columns to the output,
which breaks the plot scripts and in case there is many columns also makes it
really hard to keep track which data is in which column.

This class makes it easy to keep track of what is the data in each column,
and if the resulting table is read with pandas, the plot scripts
do not break when new columns are added.

80 lines of code, header only.

Usage
-----

```c++
#include <cmath>

#include "../DevCsvWriter.h"

int main() {
    const double g = -9.81;
    const double phi = M_PI / 4;
    const double v0 = 10;

    double vx = v0 * cos(phi);
    double vy = v0 * sin(phi);
    const double dt = 0.01;
    double t = 0, x = 0, y = 0;
    double l = 0;

    DevCsvWriter csv("projectile_45_deg.csv",
                     DevCsvWriterSettings{.precision = 5,
                                          .width = 12,
                                          .separator = "\t",
                                          .fmt_is_scientific = false});

    do {
        csv.StartNewLine();
        csv.AddColumn("t", t);
        csv.AddColumn("x", x);
        csv.AddColumn("y", y);
        // csv.AddColumn("l", l);
        csv.AddColumn("vx", vx);
        csv.AddColumn("vy", vy);
        csv.AddColumn("v", sqrt(vx * vx + vy * vy));

        const double dx = vx * dt;
        const double dy = vy * dt;
        x += dx;
        y += dy;
        l += sqrt(dx * dx + dy * dy);

        vy += g * dt;

        t += dt;
    } while (y >= 0);

    return 0;
};
```

Plot script:
```python
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
```

The plot script does not break when adding another column (arc length - l).

