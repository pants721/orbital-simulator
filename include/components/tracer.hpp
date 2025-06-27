#pragma once

#include "components/pos.hpp"
#include <cstdlib>
#include <deque>

struct Tracer {
    std::deque<Pos> points;
    size_t max_points;

    Tracer() : points(), max_points(2000) {}
};
