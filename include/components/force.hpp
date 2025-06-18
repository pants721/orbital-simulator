#pragma once

struct Force {
    double x;
    double y;

    Force() : x(0), y(0) {}
    Force(double x, double y) : x(x), y(y) {}
};
