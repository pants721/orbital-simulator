#include "components/body.hpp"
#include <string>

auto Body::serialize() -> json {
    json js;
    js["mass"] = this->mass;
    js["radius"] = this->mass;
    js["name"] = this->name;
    return js;
}

auto Body::deserialize(json js) -> Body {
    return {
        js["mass"].template get<double>(),
        js["radius"].template get<double>(),
        js["name"].template get<std::string>(),
    };
}
