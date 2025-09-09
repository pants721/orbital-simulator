#include "systems/camera_system.hpp"

#include <algorithm>
#include <entt/entt.hpp>

#include "common.hpp"

void add_camera(entt::registry &registry) {
    const auto entity = registry.create();
    registry.emplace<Camera>(entity);
}

void zoom_camera(Camera &cam, double delta) {
    cam.zoom += delta;
    cam.zoom = std::clamp(cam.zoom, kZoomMin, kZoomMax);
}

void zoom_camera_log(Camera &cam, double factor) {
    cam.zoom *= factor;
    cam.zoom = std::clamp(cam.zoom, kZoomMin, kZoomMax);
}

void pan_camera(Camera &cam, double dx, double dy) {
    cam.x += dx / cam.zoom;
    cam.y += -dy / cam.zoom;
}
