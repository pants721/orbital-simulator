#include "systems/physics_system.hpp"

#include <cmath>
#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "components/body.hpp"
#include "components/force.hpp"
#include "components/pos.hpp"
#include "components/vel.hpp"
#include "entt/entity/fwd.hpp"
#include "util.hpp"

void reset_forces(entt::registry &registry) {
    auto view = registry.view<Force>();
    for (auto [entity, force] : view.each()) {
        force.x = 0;
        force.y = 0;
    }
}

void compute_gravity_forces(entt::registry &registry) {
    auto view = registry.view<Body, Pos, Force>();

    for (auto [entity_a, body_a, pos_a, force_a] : view.each()) {
        auto &mass_a = body_a.mass;

        for (auto [entity_b, body_b, pos_b, force_b] : view.each()) {
            if (entity_a == entity_b) continue;

            auto &mass_b = body_b.mass;

            float dx = pos_b.x - pos_a.x;
            float dy = pos_b.y - pos_a.y;
            float d_sq = dx * dx + dy * dy;
            float dist = std::sqrt(d_sq);

            float force_mag = G_CONST * mass_a * mass_b / dist;
            float fx = force_mag * dx / dist;
            float fy = force_mag * dy / dist;

            force_a.x += fx;
            force_a.y += fy;
        }
    }
}

void apply_gravity_forces(entt::registry &registry, float dt) {
    auto view = registry.view<Body, Vel, Force>();

    for (auto [entity, body, vel, force] : view.each()) {
        float ax = force.x / body.mass;
        float ay = force.y / body.mass;

        vel.dx += ax * dt;
        vel.dy += ay * dt;
        if (body.name == "Earth") {
            std::cout << "Acc: "<< ax << ", " << ay << std::endl;
            std::cout << "Vel: "<< vel.dx << ", " << vel.dy << std::endl;
        }
    }
}

void velocity(entt::registry &registry, float dt) {
    auto view = registry.view<Pos, Vel>();
    for (auto [entity, pos, vel] : view.each()) {
        pos.x += vel.dx * dt;
        pos.y += vel.dy * dt;
    }
}

void gravity(entt::registry &registry, float dt) {
    auto view = registry.view<Body, Vel>();
    for (auto [entity, body, vel] : view.each()) {
        vel.dy += -90.8 * dt;
    }
}
