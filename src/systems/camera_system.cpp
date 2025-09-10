#include "systems/camera_system.hpp"

#include <algorithm>
#include <cstdio>
#include <entt/entt.hpp>
#include <optional>

#include "common.hpp"
#include "components/follow_target.hpp"
#include "components/pos.hpp"
#include "entt/entity/helper.hpp"

void update_camera(entt::registry &registry) {
    camera_follow_target(registry);
}

void add_camera(entt::registry &registry) {
    const auto entity = registry.create();
    registry.emplace<FollowTarget>(entity);
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

void camera_follow_target(entt::registry &registry) {
    auto view = registry.view<Camera, FollowTarget>();

    for (auto [entity, cam, follow_target] : view.each()) {
        if (!follow_target.target.has_value()) {
            break;
        }
        auto target_pos = registry.get<Pos>(follow_target.target.value());
        cam.x = target_pos.x;
        cam.y = target_pos.y;
    }
}

void set_camera_follow_target(entt::registry &registry, Camera &cam, std::optional<entt::entity> target) {
    const auto cam_entity = entt::to_entity(registry, cam);
    if (registry.all_of<FollowTarget>(cam_entity)) {
        FollowTarget &curr_target = registry.get<FollowTarget>(cam_entity);
        curr_target.target = target;
    }
}

void set_camera_follow_none(entt::registry &registry, Camera &cam) {
    set_camera_follow_target(registry, cam, std::nullopt);
}
