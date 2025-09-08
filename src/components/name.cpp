#include "components/name.hpp"


#include <nlohmann/json.hpp>
using json = nlohmann::json;

// XXX: idk if i should serialize the value part. prob confusing not to
auto Name::serialize() -> json {
    json js;
    js["value"] = this->value;
    return js;
}

auto Name::deserialize(json js) -> Name {
    return Name(js["value"].template get<std::string>());
}
