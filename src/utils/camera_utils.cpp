#include "utils/camera_utils.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
#include "SFML/System/Vector2.hpp"
#include "components/pos.hpp"

Pos to_screen_pos(Pos &world_pos, Camera &cam, sf::RenderWindow &window) {
    sf::Vector2f screen_center(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    return Pos((world_pos.x - cam.x) * cam.zoom + screen_center.x,
                        (world_pos.y - cam.y) * cam.zoom + screen_center.y);
}

Pos to_world_pos(Pos &screen_pos, Camera &cam, sf::RenderWindow &window) {
    sf::Vector2f screen_center(window.getSize().x / 2.0f, window.getSize().y / 2.0f);
    return Pos((screen_pos.x - screen_center.x) / cam.zoom + cam.x,
               -(screen_pos.y - screen_center.y) / cam.zoom + cam.y);
}
