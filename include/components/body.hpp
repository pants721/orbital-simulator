#pragma once

#include <string>

struct Body {
  double mass;
  double radius;
  std::string name;

  Body(double mass, double radius, std::string name)
      : mass(mass), radius(radius), name(std::move(name)) {}
};
