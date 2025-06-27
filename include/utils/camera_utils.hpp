#pragma once

#include <SFML/Graphics.hpp>
#include "components/camera.hpp"
#include "components/pos.hpp"

Pos to_screen_pos(Pos &world_pos, Camera &cam, sf::RenderWindow &window);
Pos to_world_pos(Pos &screen_pos, Camera &cam, sf::RenderWindow &window);
