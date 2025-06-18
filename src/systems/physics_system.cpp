#include "systems/physics_system.hpp"

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

#include "components/pos.hpp"
#include "components/vel.hpp"

void velocity(entt::registry &registry, float dt) {
    auto view = registry.view<Pos, Vel>();
    for (auto [entity, pos, vel] : view.each()) {
        pos.x += vel.dx * dt;
        pos.y += vel.dy * dt;
    }
}

void gravity(entt::registry &registry, float dt) {
    auto view = registry.view<Vel>();
    for (auto [entity, vel] : view.each()) {
        vel.dy += -90.8 * dt;
    }
}
