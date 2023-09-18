#ifndef VEC3_H
#define VEC3_H

class Vec3 {
  public:
    float x, y, z;

    Vec3();
    Vec3(float x, float y, float z);

    Vec3 operator+(const Vec3& v2) const;
    Vec3 operator-(const Vec3& v2) const;
    float operator*(const Vec3& v2) const; // Dot product
    Vec3 operator*(const float& s) const; // Scalar multiplication

    float norm() const;
    Vec3 normalize() const;
};

#endif