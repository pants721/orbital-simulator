#pragma once

#include "components/camera.hpp"
#include "components/pos.hpp"
#include "entt/entity/fwd.hpp"
#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

void render_bodies(entt::registry &registry, sf::RenderWindow &window);
void update_tracers(entt::registry &registry);
void render_tracers(entt::registry &registry, sf::RenderWindow &window);
