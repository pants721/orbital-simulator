#include "systems/render_system.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <entt/entt.hpp>

#include "components/camera.hpp"
#include "components/pos.hpp"
#include "components/vel.hpp"
#include "components/body.hpp"

void render_bodies(entt::registry &registry, sf::RenderWindow &window) {
    auto cam_view = registry.view<Camera>();
    // XXX: ERROR LOGGING
    if (cam_view.empty()) return;
    Camera &cam = cam_view.get<Camera>(cam_view.front());

    auto view = registry.view<const Body, Pos, Vel>();

    for (auto [entity, body, pos, vel] : view.each()) {
        Pos screen_pos = world_pos_to_screen(pos, cam, window);
        double screen_radius = std::max(body.radius * cam.zoom, 5.0);

        // culling
        if (screen_pos.x + screen_radius < 0 || screen_pos.x - screen_radius > window.getSize().x ||
            screen_pos.y + screen_radius < 0 || screen_pos.y - screen_radius > window.getSize().y) {
            continue;
        }

        sf::CircleShape shape(screen_radius);
        if (body.name == "Earth") {
            shape.setFillColor(sf::Color::Blue);
        } else if (body.name == "Sun") {
            shape.setFillColor(sf::Color::Red);
        } else if (body.name == "Moon") {
            shape.setFillColor(sf::Color::White);
        } else {
            shape.setFillColor(sf::Color::Green);
        }
        shape.setPosition(screen_pos.x - screen_radius, screen_pos.y - screen_radius);
        window.draw(shape);
    }
}

Pos world_pos_to_screen(Pos &world_pos, Camera &camera, sf::RenderWindow &window) {
    int window_w = window.getSize().x;
    int window_h = window.getSize().y;
    double screen_x = (world_pos.x - camera.x) * camera.zoom + window_w / 2.0;
    double screen_y = (world_pos.y * -1.0 - camera.y) * camera.zoom + window_h / 2.0;
    return Pos(screen_x, screen_y);
}

