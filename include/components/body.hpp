#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;

struct Body {
    double mass;
    double radius;

    Body(double mass, double radius) : mass(mass), radius(radius) {}

    // TODO(pants): ADD #IFDEF ENABLE_JSON
    auto serialize() -> json;
    static auto deserialize(json js) -> Body;
};
