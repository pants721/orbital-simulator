#pragma once

#include <string>

#include <nlohmann/json.hpp>
using json = nlohmann::json;

struct Body {
    double mass;
    double radius;
    std::string name;

    Body(double mass, double radius, std::string name)
    : mass(mass), radius(radius), name(std::move(name)) {}

    // TODO(pants): ADD #IFDEF ENABLE_JSON
    auto serialize() -> json;
    static auto deserialize(json js) -> Body;
};
