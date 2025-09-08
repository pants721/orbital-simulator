#pragma once

#include <string>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

struct Name {
    std::string value;

    explicit Name(std::string value) : value(std::move(value)) {}

    auto serialize() -> json;
    static auto deserialize(json js) -> Name;

};
