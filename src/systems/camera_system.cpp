#include <entt/entt.hpp>

#include "systems/camera_system.hpp"

#include <algorithm>
#include <iostream>

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

void pan_camera(Camera &cam, double dx, double dy, double dt) {
    std::cout << cam.zoom << std::endl;
    cam.x += dx * (1.0 / cam.zoom) * dt;
    cam.y += dy * (1.0 / cam.zoom) * dt;
}
