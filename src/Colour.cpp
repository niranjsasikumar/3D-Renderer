#include "Colour.h"
#include <stdexcept>

void validateRange(const float& value) {
  if (value < 0.0f || value > 1.0f)
    throw std::invalid_argument("Invalid RGB value");
}

Colour::Colour() {}

Colour::Colour(float red, float green, float blue) {
  validateRange(red);
  validateRange(green);
  validateRange(blue);
  r = red;
  g = green;
  b = blue;
}

Colour::Colour(const Vec3& vec) {
  float max = std::max(vec.x, std::max(vec.y, vec.z));
  if (max > 1.0f) {
    r = vec.x / max;
    g = vec.y / max;
    b = vec.z / max;
  } else {
    r = vec.x;
    g = vec.y;
    b = vec.z;
  }
}

float Colour::getR() const { return r; }

float Colour::getG() const { return g; }

float Colour::getB() const { return b; }

Vec3 Colour::operator+(const Colour& c2) const {
  return Vec3(r + c2.r, g + c2.g, b + c2.b);
}

// Scalar multiplication
Vec3 Colour::operator*(const float& s) const {
  return Vec3(s * r, s * g, s * b);
}