#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;

struct Vel {
    double dx;
    double dy;

    Vel(double dx, double dy) : dx(dx), dy(dy) {}

    auto serialize() -> json;
    static auto deserialize(json js) -> Vel;
};

