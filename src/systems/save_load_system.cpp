#include "systems/save_load_system.hpp"
#include "components/color.hpp"
#include "components/force.hpp"
#include "components/name.hpp"
#include "components/tracer.hpp"

#include <entt/entt.hpp>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "components/body.hpp"
#include "components/pos.hpp"
#include "components/vel.hpp"
#include "components/color.hpp"

auto add_body(entt::registry &registry, Name name, Body body, Pos pos, Vel vel, Color color) -> entt::entity {
    const auto entity = registry.create();
    registry.emplace<Body>(entity, body.mass, body.radius);
    registry.emplace<Name>(entity, name.value);
    registry.emplace<Pos>(entity, pos.x, pos.y);
    registry.emplace<Vel>(entity, vel.dx, vel.dy);
    registry.emplace<Force>(entity);
    registry.emplace<Color>(entity, color.r, color.g, color.b);
    registry.emplace<Tracer>(entity);
    return entity;
}

auto serialize_registry_state(entt::registry &registry) -> json {
    auto view = registry.view<Name, Color, Body, Pos, Vel>();
    json state_json = json::array();

    for (auto [entity, name, color, body, pos, vel] : view.each()) {
        json entity_json;

        json name_json = name.serialize();
        entity_json["name"] = name_json;

        json color_json = color.serialize();
        entity_json["color"] = color_json;

        json body_json = body.serialize();
        entity_json["body"] = body_json;

        json pos_json = pos.serialize();
        entity_json["pos"] = pos_json;

        json vel_json = vel.serialize();
        entity_json["vel"] = vel_json;

        state_json.push_back(entity_json);
    }

    return state_json;
}

void save_registry(entt::registry &registry, const std::string &file_path) {
    json state_json = serialize_registry_state(registry);
    std::ofstream file(file_path);
    file << state_json;
}

void deserialize_registry(entt::registry &registry, const json &state_json) {
    for (auto entity : state_json) {
        Name name = Name::deserialize(entity["name"]);
        Color color = Color::deserialize(entity["color"]);
        Body body = Body::deserialize(entity["body"]);
        Pos pos = Pos::deserialize(entity["pos"]);
        Vel vel = Vel::deserialize(entity["vel"]);
        add_body(registry, name, body, pos, vel, color);
    }
}

void load_registry_state(entt::registry &registry, const std::string &file_path) {
    std::ifstream file(file_path);
    json state_json;
    file >> state_json;
    deserialize_registry(registry, state_json);
}
