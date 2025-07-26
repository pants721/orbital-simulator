#include "systems/render_system.hpp"
#include <SFML/Graphics.hpp>
#include <algorithm>
#include <entt/entt.hpp>

#include "SFML/System/Vector2.hpp"
#include "components/camera.hpp"
#include "components/color.hpp"
#include "components/pos.hpp"
#include "components/tracer.hpp"
#include "components/vel.hpp"
#include "components/body.hpp"
#include "entt/entity/fwd.hpp"
#include "common.hpp"
#include "utils/camera_utils.hpp"

void render_bodies(entt::registry &registry, sf::RenderWindow &window) {
    auto cam_view = registry.view<Camera>();
    // XXX: ERROR LOGGING
    if (cam_view.empty()) return;
    Camera &cam = cam_view.get<Camera>(cam_view.front());

    auto view = registry.view<const Body, Pos, Vel, Color>();

    for (auto [entity, body, pos, vel, color] : view.each()) {
        Pos screen_pos = to_screen_pos(pos, cam, window);
        double screen_radius = std::max(body.radius * cam.zoom, kMinRadius);

        // culling
        if (screen_pos.x + screen_radius < 0 || screen_pos.x - screen_radius > window.getSize().x ||
            screen_pos.y + screen_radius < 0 || screen_pos.y - screen_radius > window.getSize().y) {
            continue;
        }

        sf::CircleShape shape(static_cast<float>(screen_radius));
        shape.setFillColor(sf::Color(color.r, color.g, color.b));
        shape.setPosition(static_cast<float>(screen_pos.x - screen_radius), static_cast<float>(screen_pos.y - screen_radius));
        window.draw(shape);
    }
}

void update_tracers(entt::registry &registry) {
    auto view = registry.view<Pos, Tracer>();
    for (auto [entity, pos, tracer] : view.each()) {
        tracer.points.push_back(pos);

        if (tracer.points.size() > tracer.max_points) {
            tracer.points.pop_front();
        }
    }
}

void render_tracers(entt::registry &registry, sf::RenderWindow &window) {
    auto cam_view = registry.view<Camera>();
    // XXX: ERROR LOGGING
    if (cam_view.empty()) return;
    Camera &cam = cam_view.get<Camera>(cam_view.front());

    auto view = registry.view<Tracer, Color>();

    for (auto [entity, tracer, color] : view.each()) {
        sf::VertexArray line(sf::LineStrip, tracer.points.size());
        for (size_t i = 0; i < tracer.points.size(); ++i) {
            Pos screen_pos = to_screen_pos(tracer.points[i], cam, window);
            line[i].position = sf::Vector2<float>(
                static_cast<float>(screen_pos.x), 
                static_cast<float>(screen_pos.y)
            );

            line[i].color = sf::Color(
                color.r, color.g, color.b,
                static_cast<sf::Uint8>(
                    (static_cast<float>(i) / tracer.points.size()) * 255.0F // NOLINT
                )
            );  // Fading effect
        }

        window.draw(line);
    }
}

