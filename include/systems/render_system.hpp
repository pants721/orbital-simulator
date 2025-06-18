#pragma once

#include "components/camera.hpp"
#include "components/pos.hpp"
#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

void render_bodies(entt::registry &registry, sf::RenderWindow &window);
Pos world_pos_to_screen(Pos &world_pos, Camera &camera, sf::RenderWindow &window);
