#include "Sphere.h"
#include <stdexcept>

void validateRange(
  const float& value,
  const float& min,
  const float& max,
  const std::string& name
) {
  if (value < min || value > max)
    throw std::invalid_argument("Invalid " + name + " value");
}

Sphere::Sphere() {}

Sphere::Sphere(
  Vec3 center,
  float radius,
  Colour colour,
  float drc,
  float src,
  float specular_exponent,
  float reflectivity
) : center(center), colour(colour) {
  if (radius <= 0.0f)
    throw std::invalid_argument("Invalid radius value");
  
  validateRange(drc, 0.0f, 1.0f, "diffuse reflection coefficient");
  validateRange(src, 0.0f, 1.0f, "specular reflection coefficient");
  validateRange(specular_exponent, 0.0f, 2000.0f, "specular exponent");
  validateRange(reflectivity, 0.0f, 1.0f, "reflectivity");
  
  this->radius = radius;
  this->drc = drc;
  this->src = src;
  this->specular_exponent = specular_exponent;
  this->reflectivity = reflectivity;
}

Vec3 Sphere::getCenter() const { return center; }

float Sphere::getRadius() const { return radius; }

Colour Sphere::getColour() const { return colour; }

float Sphere::getDrc() const { return drc; }

float Sphere::getSrc() const { return src; }

float Sphere::getSpecularExponent() const { return specular_exponent; }

float Sphere::getReflectivity() const { return reflectivity; }