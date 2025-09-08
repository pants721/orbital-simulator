#pragma once

#include <entt/entt.hpp>

void reset_forces(entt::registry &registry);

void compute_gravity_forces(entt::registry &registry);

void apply_gravity_forces(entt::registry &registry, double dt);

void velocity(entt::registry &registry, double dt);
