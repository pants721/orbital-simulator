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
#define WINDOW_W 1920
#define WINDOW_H 1080

#define TIME_SCALE 3.15e6

// 1 astronomical unit (AU) in meters
constexpr double AU = 1.496e11;

// Sun mass (center of simulation)
constexpr double SUN_MASS = 1.989e30;

int main() {
    entt::registry registry;
    add_camera(registry);
    // Sun
    add_body(registry, SUN_MASS, 6.9634e8, "Sun",
             Pos(0.0, 0.0), Vel(0.0, 0.0),
             Color(255, 204, 0)); // Yellow

    // Mercury
    add_body(registry, 3.285e23, 2.44e6, "Mercury",
             Pos(0.387 * AU, 0.0),
             Vel(0.0, std::sqrt(G_CONST * SUN_MASS / (0.387 * AU))),
             Color(169, 169, 169)); // Gray

    // Venus
    add_body(registry, 4.867e24, 6.052e6, "Venus",
             Pos(0.723 * AU, 0.0),
             Vel(0.0, std::sqrt(G_CONST * SUN_MASS / (0.723 * AU))),
             Color(255, 223, 196)); // Pale yellow

    // Earth
    add_body(registry, 5.972e24, 6.371e6, "Earth",
             Pos(1.0 * AU, 0.0),
             Vel(0.0, std::sqrt(G_CONST * SUN_MASS / (1.0 * AU))),
             Color(0, 102, 204)); // Blue

    // Mars
    add_body(registry, 6.39e23, 3.39e6, "Mars",
             Pos(1.524 * AU, 0.0),
             Vel(0.0, std::sqrt(G_CONST * SUN_MASS / (1.524 * AU))),
             Color(255, 100, 100)); // Reddish

    // Jupiter
    add_body(registry, 1.898e27, 6.9911e7, "Jupiter",
             Pos(5.204 * AU, 0.0),
             Vel(0.0, std::sqrt(G_CONST * SUN_MASS / (5.204 * AU))),
             Color(255, 165, 0)); // Orange

    // Saturn
    add_body(registry, 5.683e26, 5.8232e7, "Saturn",
             Pos(9.582 * AU, 0.0),
             Vel(0.0, std::sqrt(G_CONST * SUN_MASS / (9.582 * AU))),
             Color(210, 180, 140)); // Tan

    // Uranus
    add_body(registry, 8.681e25, 2.5362e7, "Uranus",
             Pos(19.2 * AU, 0.0),
             Vel(0.0, std::sqrt(G_CONST * SUN_MASS / (19.2 * AU))),
             Color(173, 216, 230)); // Light blue

    // Neptune
    add_body(registry, 1.024e26, 2.4622e7, "Neptune",
             Pos(30.05 * AU, 0.0),
             Vel(0.0, std::sqrt(G_CONST * SUN_MASS / (30.05 * AU))),
             Color(72, 61, 139)); // Dark blue

    // Optional: Pluto (dwarf planet)
    add_body(registry, 1.309e22, 1.188e6, "Pluto",
             Pos(39.48 * AU, 0.0),
             Vel(0.0, std::sqrt(G_CONST * SUN_MASS / (39.48 * AU))),
             Color(220, 220, 220)); // Light gray
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

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
            auto cam_view = registry.view<Camera>();
            Camera &cam = registry.get<Camera>(cam_view.front());
            pan_camera(cam, 0.0, 1.0);
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
