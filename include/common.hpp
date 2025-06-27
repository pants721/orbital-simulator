#pragma once

#include <string>

// Rendering
const std::string WINDOW_TITLE = "Orbital Simulation";
constexpr double WINDOW_W = 1920.0;
constexpr double WINDOW_H = 1080.0;
constexpr double ZOOM_MIN = 1.0e-90;
constexpr double ZOOM_MAX = 1000.0;
constexpr double ZOOM_FACTOR = 0.01;
constexpr double MIN_RADIUS = 1.0;
constexpr double PAN_SPEED = 4.0;

constexpr double TIME_SCALE = 5.0e5;

// Physics
constexpr double AU = 1.496e11;
const double G_CONST = 6.6743e-11;

// MISC
constexpr double SUN_MASS = 1.989e30;
