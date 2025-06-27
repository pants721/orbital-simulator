#pragma once

#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

#include "components/color.hpp"
#include "components/pos.hpp"
#include "components/vel.hpp"

const double G_CONST = 6.6743e-11;

entt::entity add_body(entt::registry &registry, double mass, double radius, 
              std::string name, Pos pos, Vel vel, Color color);

void reset_forces(entt::registry &registry);

void compute_gravity_forces(entt::registry &registry);

void apply_gravity_forces(entt::registry &registry, double dt);

void velocity(entt::registry &registry, double dt);


