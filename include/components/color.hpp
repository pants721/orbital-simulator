#pragma once

#include <nlohmann/json.hpp>
using json = nlohmann::json;

#include <cstdint>

struct Color {
    uint8_t r;
    uint8_t g;
    uint8_t b;

    Color(uint8_t r, uint8_t g, uint8_t b) : r(r), g(g), b(b) {}

    auto serialize() -> json;
    static auto deserialize(json js) -> Color;
};
