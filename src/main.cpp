#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <iostream>
#include <string>

#include "SFML/Window/Keyboard.hpp"
#include "components/camera.hpp"
#include "components/pos.hpp"
#include "components/vel.hpp"
#include "components/body.hpp"

#include "systems/render_system.hpp"
#include "systems/physics_system.hpp"
#include "systems/camera_system.hpp"

#define WINDOW_TITLE "Orbital Simulation"
#define WINDOW_W 1280
#define WINDOW_H 960

#define TIME_SCALE 3600.0

int main() {
    entt::registry registry;
    add_camera(registry);

    // add_body(registry, 1.9891e30, 6.9634e8, "Sun", Pos(0.0, 0.0), Vel(0.0, 0.0));
    // add_body(registry, 5.972e24, 6.371e6, "Earth", Pos(1.496e11, 0.0), Vel(0.0, 29780));
    // add_body(registry, 7.342e22, 1.737e6, "Moon", Pos(1.496e11 + 3.844e8, 0.0), Vel(0.0, 29780 + 1022));
    add_body(registry, 5.92e21, 300000, "Earth", Pos(0.0, 0.0), Vel(0.0, 0.0));
    add_body(registry, 1.0e15, 10000, "Moon", Pos(1.0e6, 0.0), Vel(0.0, 628.5));

    sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), WINDOW_TITLE);
    sf::Clock deltaClock;

    // Main loop
    while (window.isOpen()) {
        double dt = deltaClock.restart().asSeconds() * TIME_SCALE;

        sf::Event ev;
        
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) {
                window.close();
            }
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Q)) {
            auto cam_view = registry.view<Camera>();
            Camera &cam = registry.get<Camera>(cam_view.front());
            zoom_camera_log(cam, 0.999);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::E)) {
            auto cam_view = registry.view<Camera>();
            Camera &cam = registry.get<Camera>(cam_view.front());
            zoom_camera_log(cam, 1.001);
        }

        // world logic
        reset_forces(registry);
        compute_gravity_forces(registry);
        apply_gravity_forces(registry, dt);
        velocity(registry, dt);
        auto view = registry.view<Body, Pos, Vel>();
        for (auto [e, b, p, v] : view.each()) {
            std::cout << b.name << ": pos=(" << p.x << ", " << p.y << "), vel=(" << v.dx << ", " << v.dy << ")\n";
        }

        // rendering
        window.clear();
        render_bodies(registry, window);
        window.display();
    }

    return EXIT_SUCCESS;
}
