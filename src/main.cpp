#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <string>

#include "SFML/Window/ContextSettings.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/WindowStyle.hpp"
#include "components/body.hpp"
#include "components/camera.hpp"
#include "components/pos.hpp"
#include "components/vel.hpp"

#include "entt/entity/fwd.hpp"
#include "nlohmann/json.hpp"
using json = nlohmann::json;
#include "systems/render_system.hpp"
#include "systems/physics_system.hpp"
#include "systems/camera_system.hpp"
#include "common.hpp"
#include "systems/save_load_system.hpp"

auto main() -> int {
    entt::registry registry;
    add_camera(registry);

    load_registry_state(registry, "data.json");

    // SFML setup
    sf::ContextSettings settings;
    settings.antialiasingLevel = 8;

    sf::RenderWindow window(sf::VideoMode(kWindowW, kWindowH), kWindowTitle, sf::Style::Default, settings);
    sf::Clock delta_clock;

    while (window.isOpen()) {
        double delta_t = delta_clock.restart().asSeconds() * kTimeScale;

        sf::Event event;

        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
        }

        auto cam_view = registry.view<Camera>();
        Camera &cam = registry.get<Camera>(cam_view.front());

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
            zoom_camera_log(cam, 1.0 - kZoomFactor);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
            zoom_camera_log(cam, 1.0 + kZoomFactor);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            pan_camera(cam, 0.0, kPanSpeed);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
            pan_camera(cam, 0.0, -kPanSpeed);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
            pan_camera(cam, -kPanSpeed, 0.0);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
            pan_camera(cam, kPanSpeed, 0.0);
        }

        // world logic
        reset_forces(registry);
        compute_gravity_forces(registry);
        apply_gravity_forces(registry, delta_t);
        velocity(registry, delta_t);

        // rendering
        window.clear();
        update_tracers(registry);
        render_tracers(registry, window);
        render_bodies(registry, window);
        window.display();
    }

    return EXIT_SUCCESS;
}
