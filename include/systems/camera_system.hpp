#pragma once

#include <entt/entt.hpp>

#include "components/camera.hpp"

#define ZOOM_MIN 0.0
#define ZOOM_MAX 1000.0
#define BASE_PAN_SPEED 1000000.0

void add_camera(entt::registry &registry);
void zoom_camera(Camera &cam, double delta);
void zoom_camera_log(Camera &cam, double factor);
void pan_camera(Camera &cam, double dx, double dy);
