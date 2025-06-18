#pragma once

#include <string>

struct Body {
  float mass;
  float radius;
  std::string name;

  Body(float mass, float radius, std::string name)
      : mass(mass), radius(radius), name(std::move(name)) {}
};
