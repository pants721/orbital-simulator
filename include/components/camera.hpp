#pragma once

#include "common.hpp"

struct Camera {
    double x{}, y{};
    double zoom;

    Camera() : zoom(kZoomDefault) {}
};
