#pragma once

#include "common.hpp"

struct Camera {
    // Maybe this should be a Pos component
    double x{}, y{};
    double zoom;

    Camera() : zoom(kZoomDefault) {}
};
