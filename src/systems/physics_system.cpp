#include "systems/physics_system.hpp"

#include <cmath>
#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>

#include "components/body.hpp"
#include "components/color.hpp"
#include "components/force.hpp"
#include "components/pos.hpp"
#include "components/tracer.hpp"
#include "components/vel.hpp"
#include "entt/entity/fwd.hpp"

entt::entity add_body(entt::registry &registry, double mass, double radius, 
              std::string name, Pos pos, Vel vel, Color color) {
    const auto entity = registry.create();
    registry.emplace<Body>(entity, mass, radius, name);
    registry.emplace<Pos>(entity, pos.x, pos.y);
    registry.emplace<Vel>(entity, vel.dx, vel.dy);
    registry.emplace<Force>(entity);
    // XXX: IDK IF COLOR AND TRACER SHOULD BE IN PHYSICS SYSTEM. MAYBE REPLACE
    // WITH RENDERABLE COMPONENT
    registry.emplace<Color>(entity, color.r, color.g, color.b);
    registry.emplace<Tracer>(entity);
    return entity;
}


void reset_forces(entt::registry &registry) {
    auto view = registry.view<Force>();
    for (auto [entity, force] : view.each()) {
        force.x = 0;
        force.y = 0;
    }
}

void compute_gravity_forces(entt::registry &registry) {
    auto view = registry.view<Body, Pos, Force>();
    std::vector<entt::entity> entities(view.begin(), view.end());

    for (size_t i = 0; i < entities.size(); ++i) {
        auto entity_a = entities[i];
        auto [body_a, pos_a, force_a] = view.get<Body, Pos, Force>(entity_a);

        for (size_t j = i + 1; j < entities.size(); ++j) {
            auto entity_b = entities[j];
            auto [body_b, pos_b, force_b] = view.get<Body, Pos, Force>(entity_b);

            double dx = pos_b.x - pos_a.x;
            double dy = pos_b.y - pos_a.y;
            double d_sq = dx * dx + dy * dy;
            double dist = std::sqrt(d_sq);

            if (dist == 0.0) continue;

            double force_mag = G_CONST * body_a.mass * body_b.mass / d_sq;
            double fx = force_mag * dx / dist;
            double fy = force_mag * dy / dist;

            force_a.x += fx;
            force_a.y += fy;

            force_b.x -= fx;
            force_b.y -= fy;
        }
    }
}

void apply_gravity_forces(entt::registry &registry, double dt) {
    auto view = registry.view<Body, Vel, Force>();

    for (auto [entity, body, vel, force] : view.each()) {
        double ax = force.x / body.mass;
        double ay = force.y / body.mass;

        vel.dx += ax * dt;
        vel.dy += ay * dt;
    }
}

void velocity(entt::registry &registry, double dt) {
    auto view = registry.view<Pos, Vel>();
    for (auto [entity, pos, vel] : view.each()) {
        pos.x += vel.dx * dt;
        pos.y += vel.dy * dt;
    }
}
