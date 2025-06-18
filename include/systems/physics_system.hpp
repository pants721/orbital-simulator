#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

void reset_forces(entt::registry &registry);

void compute_gravity_forces(entt::registry &registry);

void apply_gravity_forces(entt::registry &registry, float dt);

void velocity(entt::registry &registry, float dt);

void gravity(entt::registry &registry, float dt);


