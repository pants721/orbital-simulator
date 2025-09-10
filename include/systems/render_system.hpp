#pragma once

#include "entt/entity/fwd.hpp"
#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

void render(entt::registry &registry, sf::RenderWindow &window);
void render_bodies(entt::registry &registry, sf::RenderWindow &window);
void update_tracers(entt::registry &registry);
void render_tracers(entt::registry &registry, sf::RenderWindow &window);
