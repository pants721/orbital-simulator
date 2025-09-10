#pragma once

#include "entt/entity/fwd.hpp"
#include <entt/entt.hpp>
#include <optional>

struct FollowTarget {
    std::optional<entt::entity> target;

    FollowTarget() : target(std::nullopt) {};
    explicit FollowTarget(entt::entity target) : target(std::optional(target)) {};
};

