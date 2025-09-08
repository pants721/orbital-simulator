#include "components/pos.hpp"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

auto Pos::serialize() -> json {
    json js;
    js["x"] = this->x;
    js["y"] = this->y;
    return js;
}

auto Pos::deserialize(json js) -> Pos {
    return {
        js["x"].template get<double>(),
        js["y"].template get<double>(),
    };
}
