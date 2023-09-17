#include "Vec3.h"
#include <cmath>

Vec3::Vec3() {}

Vec3::Vec3(float x, float y, float z) : x(x), y(y), z(z) {}

Vec3 Vec3::operator+(const Vec3& v2) const {
  return Vec3(x + v2.x, y + v2.y, z + v2.z);
}

Vec3 Vec3::operator-(const Vec3& v2) const {
  return Vec3(x - v2.x, y - v2.y, z - v2.z);
}

// Dot product
float Vec3::operator*(const Vec3& v2) const {
  return x * v2.x + y * v2.y + z * v2.z;
}

// Scalar multiplication
Vec3 Vec3::operator*(const float& s) const {
  return Vec3(s * x, s * y, s * z);
}

float Vec3::norm() const {
  return std::sqrt(x * x + y * y + z * z);
}

Vec3 Vec3::normalize() const {
  return (*this) * (1.0f / norm());
}