#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>
#include <imgui.h>
#include <imgui-SFML.h>

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <optional>
#include <ostream>
#include <string>


#include "components/body.hpp"
#include "components/camera.hpp"
#include "components/pos.hpp"
#include "components/vel.hpp"

#include "entt/entity/fwd.hpp"
#include "nlohmann/json.hpp"
#include "systems/gui_system.hpp"
using json = nlohmann::json;
#include "systems/render_system.hpp"
#include "systems/physics_system.hpp"
#include "systems/camera_system.hpp"
#include "common.hpp"
#include "systems/save_load_system.hpp"

auto main() -> int {
    entt::registry registry;
    add_camera(registry, Name("Main Camera"));

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
    ImGui::SFML::Init(window); // NOLINT

    sf::Clock delta_clock;

    while (window.isOpen()) {
        double delta_t = delta_clock.restart().asSeconds() * kTimeScale;

        while (const std::optional event = window.pollEvent()) {
            ImGui::SFML::ProcessEvent(window, *event);

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

        // gui
        ImGui::SFML::Update(window, delta_clock.restart());

        ImGui::Begin("Settings");
        focus_body_settings(registry);
        ImGui::End();

        ImGui::Begin("Body Info");
        body_info_widget(registry);
        ImGui::End();

        // rendering
        window.clear();
        update_camera(registry);
        render(registry, window);
        ImGui::SFML::Render(window);
        window.display();
    }
    ImGui::SFML::Shutdown();

    return EXIT_SUCCESS;
}
