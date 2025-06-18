#include <entt/entt.hpp>
#include <SFML/Graphics.hpp>

#include <cstdlib>
#include <iostream>
#include <string>

#include "components/pos.hpp"
#include "components/vel.hpp"
#include "components/body.hpp"

#include "systems/render_system.hpp"
#include "systems/physics_system.hpp"

#include "util.hpp"

#define WINDOW_TITLE "Orbital Simulation"
#define WINDOW_W 1280
#define WINDOW_H 960



int main() {
    entt::registry registry;

    add_body(registry, 5.0, 100.0, "Earth", Pos(0.0, -100.0), Vel(-100.0, 0.0));
    add_body(registry, 5.0, 100.0, "Earth", Pos(-500.0, -100.0), Vel(0.0, 0.0));

    sf::RenderWindow window(sf::VideoMode(WINDOW_W, WINDOW_H), WINDOW_TITLE);
    sf::Clock deltaClock;

    // Main loop
    while (window.isOpen()) {
        float dt = deltaClock.restart().asSeconds();

        sf::Event ev;
        
        while (window.pollEvent(ev)) {
            if (ev.type == sf::Event::Closed) {
                window.close();
            }
        }

        // world logic
        velocity(registry, dt);
        gravity(registry, dt);

        // rendering
        window.clear();
        render_bodies(registry, window);
        window.display();
    }

    return EXIT_SUCCESS;
}
