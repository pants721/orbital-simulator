#pragma once

#define ZOOM_DEFAULT 1.0 / 3e8

struct Camera {
    long long int x, y;
    double zoom;

    Camera() : x(0), y(0), zoom(ZOOM_DEFAULT) {}
};
