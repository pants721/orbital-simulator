#pragma once

#include <string>

// Rendering
const std::string kWindowTitle = "Orbital Simulation";
constexpr double kWindowW = 1920.0;
constexpr double kWindowH = 1080.0;
constexpr double kZoomMin = 1.0e-90;
constexpr double kZoomMax = 1000.0;
constexpr double kZoomFactor = 0.01;
constexpr double kZoomDefault = 1.0 / 3e8;
constexpr double kMinRadius = 1.0;
constexpr double kPanSpeed = 4.0;

constexpr double kTimeScale = 5.0e5;
constexpr size_t kMaxTracerLength = 2000;

// Physics
constexpr double kAu = 1.496e11;
const double kGConst = 6.6743e-11;

// MISC
constexpr double kSunMass = 1.989e30;
