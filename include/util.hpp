#pragma once

#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

#include "components/pos.hpp"
#include "components/vel.hpp"

const double G_CONST = 6.674e-11;

void add_body(entt::registry &registry, float mass, float radius, 
              std::string name, Pos pos, Vel vel);

Pos world_to_camera_coords(Pos pos, int window_w, int window_h);
