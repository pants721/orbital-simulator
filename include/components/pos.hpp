#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;

struct Pos {
    double x;
    double y;

    Pos(double x, double y) : x(x), y(y) {}
    auto serialize() -> json;
    static auto deserialize(json js) -> Pos;
};
