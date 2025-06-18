#include <SFML/Graphics.hpp>
#include <entt/entt.hpp>

#include "components/pos.hpp"
#include "components/vel.hpp"
#include "components/body.hpp"

#include "util.hpp"

void render_bodies(entt::registry &registry, sf::RenderWindow &window) {
    auto view = registry.view<const Body, const Pos, Vel>();

    for (auto [entity, body, pos, vel] : view.each()) {
        sf::CircleShape shape(body.radius);
        shape.setFillColor(sf::Color::Red);
        Pos cam_pos = world_to_camera_coords(pos, window.getSize().x, window.getSize().y);
        shape.setPosition(cam_pos.x - body.radius, cam_pos.y - body.radius);
        window.draw(shape);
    }
}
