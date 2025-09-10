#pragma once

#include <entt/entt.hpp>

#include "components/camera.hpp"
#include "entt/entity/fwd.hpp"

void add_camera(entt::registry &registry);
// XXX:
void zoom_camera(Camera &cam, double delta);
void zoom_camera_log(Camera &cam, double factor);
void pan_camera(Camera &cam, double dx, double dy);
void camera_follow_target(entt::registry &registry);
void set_camera_follow_target(entt::registry &registry, Camera &cam, entt::entity target);
