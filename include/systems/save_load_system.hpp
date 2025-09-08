#pragma once

#include <entt/entt.hpp>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

auto serialize_registry_state(entt::registry &registry) -> json;
void save_registry(entt::registry &registry, const std::string &file_path);
