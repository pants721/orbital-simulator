#include "utils/camera_utils.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "components/pos.hpp"

auto to_screen_pos(Pos &world_pos, Camera &cam, sf::RenderWindow &window) -> Pos {
    sf::Vector2<double> screen_center(window.getSize().x / 2.0, window.getSize().y / 2.0);
    return {static_cast<double>((cam.zoom * (world_pos.x - cam.x)) + screen_center.x), // NOLINT
            static_cast<double>((cam.zoom * (world_pos.y - cam.y)) + screen_center.y)}; // NOLINT
}

auto to_world_pos(Pos &screen_pos, Camera &cam, sf::RenderWindow &window) -> Pos {
    sf::Vector2<double> screen_center(window.getSize().x / 2.0, window.getSize().y / 2.0);
    return {static_cast<double>(((screen_pos.x - screen_center.x) / cam.zoom) + cam.x), // NOLINT
            static_cast<double>((-(screen_pos.y - screen_center.y) / cam.zoom) + cam.y)}; // NOLINT
}
