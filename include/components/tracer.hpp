#pragma once

#include "components/pos.hpp"
#include "common.hpp"
#include <deque>

struct Tracer {
    std::deque<Pos> points;
    size_t max_points;

    // XXX: idk abt this constant
    Tracer() : max_points(kMaxTracerLength) {}
};
