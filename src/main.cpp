#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <ostream>
#include <string>

#include "SFML/Window/ContextSettings.hpp"
#include "SFML/Window/Keyboard.hpp"
#include "SFML/Window/WindowEnums.hpp"
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
    settings.antiAliasingLevel = 8;

    sf::RenderWindow window(
        sf::VideoMode({static_cast<unsigned int>(kWindowW), static_cast<unsigned int>(kWindowH)}), 
        kWindowTitle, 
        sf::Style::Default, 
        sf::State::Fullscreen,
        settings
    );
    sf::Clock delta_clock;

    // XXX: temp while i figure out the actual way to setup following
    auto body_view = registry.view<Name, Body, Pos>();
    for (auto [entity, name, body, pos] : body_view.each()) {
        if (name.value == "Earth") {
            auto cam_view = registry.view<Camera>();
            Camera &cam = registry.get<Camera>(cam_view.front());
            set_camera_follow_target(registry, cam, entity);
        }
    }

    while (window.isOpen()) {
        double delta_t = delta_clock.restart().asSeconds() * kTimeScale;

        while (const std::optional event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>()) {
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
        camera_follow_target(registry);
        update_tracers(registry);
        render_tracers(registry, window);
        render_bodies(registry, window);
        window.display();
    }

    return EXIT_SUCCESS;
}
