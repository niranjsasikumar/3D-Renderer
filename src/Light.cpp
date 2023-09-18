#include "Light.hpp"
#include <stdexcept>

Light::Light(Vec3 position, float intensity) : position(position) {
  if (intensity < 0.0f || intensity > 5.0f)
    throw std::invalid_argument("Invalid intensity value");
  
  this->intensity = intensity;
}

Vec3 Light::getPosition() const { return position; }

float Light::getIntensity() const { return intensity; }