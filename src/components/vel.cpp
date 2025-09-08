#include "components/vel.hpp"

#include <nlohmann/json.hpp>
using json = nlohmann::json;

auto Vel::serialize() -> json {
    json js;
    js["dx"] = this->dx;
    js["dy"] = this->dy;
    return js;
}

auto Vel::deserialize(json js) -> Vel {
    return {
        js["dx"].template get<double>(),
        js["dy"].template get<double>(),
    };
}
