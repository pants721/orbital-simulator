#include "systems/save_load_system.hpp"
#include "entt/entity/fwd.hpp"

#include <entt/entt.hpp>
#include <filesystem>
#include <fstream>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include "components/body.hpp"
#include "components/pos.hpp"
#include "components/vel.hpp"

auto serialize_registry_state(entt::registry &registry) -> json {
    auto view = registry.view<Body, Pos, Vel>();
    json state_json = json::array();

    for (auto [entity, body, pos, vel] : view.each()) {
        json entity_json;

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
