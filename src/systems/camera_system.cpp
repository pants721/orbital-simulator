#include <entt/entt.hpp>

#include "systems/camera_system.hpp"
#include <algorithm>


void add_camera(entt::registry &registry) {
    const auto entity = registry.create();
    registry.emplace<Camera>(entity);
}

void zoom_camera(Camera &cam, double delta) {
    cam.zoom += delta;
    cam.zoom = std::clamp(cam.zoom, ZOOM_MIN, ZOOM_MAX);
}

void zoom_camera_log(Camera &cam, double factor) {
    cam.zoom *= factor;
    cam.zoom = std::clamp(cam.zoom, ZOOM_MIN, ZOOM_MAX);
}

void pan_camera(Camera &cam, double dx, double dy) {
    cam.x += dx;
    cam.y += dy;
}
