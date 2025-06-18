#include "util.hpp"

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

#include "components/pos.hpp"
#include "components/vel.hpp"
#include "components/force.hpp"
#include "components/body.hpp"

void add_body(entt::registry &registry, float mass, float radius, 
              std::string name, Pos pos, Vel vel) {
    const auto entity = registry.create();
    registry.emplace<Body>(entity, mass, radius, name);
    registry.emplace<Pos>(entity, pos.x, pos.y);
    registry.emplace<Vel>(entity, vel.dx, vel.dy);
    registry.emplace<Force>(entity);
}

Pos world_to_camera_coords(Pos pos, int window_w, int window_h) {
    int center_x = window_w / 2;
    int center_y = window_h / 2;
    // SFML by default makes -y go up instead of down
    pos.y *= -1.0;

    Pos pos2(pos.x + center_x, pos.y + center_y);

    return pos2;
}
