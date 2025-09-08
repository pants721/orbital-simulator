#pragma once

#include "components/body.hpp"
#include "components/color.hpp"
#include "components/name.hpp"
#include "components/pos.hpp"
#include "components/vel.hpp"
#include "entt/entity/fwd.hpp"
#include <entt/entt.hpp>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

auto add_body(entt::registry &registry, Name name, Body body, Pos pos, Vel vel, Color color) -> entt::entity;
auto serialize_registry_state(entt::registry &registry) -> json;
void save_registry(entt::registry &registry, const std::string &file_path);
void deserialize_registry(entt::registry &registry, const json &state_json);

