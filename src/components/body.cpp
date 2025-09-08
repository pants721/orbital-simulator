#include "components/body.hpp"

auto Body::serialize() -> json {
    json js;
    js["mass"] = this->mass;
    js["radius"] = this->radius;
    return js;
}

auto Body::deserialize(json js) -> Body {
    return {
        js["mass"].template get<double>(),
        js["radius"].template get<double>(),
    };
}
