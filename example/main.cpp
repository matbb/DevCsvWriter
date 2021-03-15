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
