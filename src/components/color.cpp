#include "components/color.hpp"

#include <cstdint>
#include <nlohmann/json.hpp>
using json = nlohmann::json;

auto Color::serialize() -> json {
    json js;
    js["r"] = this->r;
    js["g"] = this->g;
    js["b"] = this->b;
    return js;
}

auto Color::deserialize(json js) -> Color {
    return {
        js["r"].template get<uint8_t>(),
        js["g"].template get<uint8_t>(),
        js["b"].template get<uint8_t>(),
    };
}
