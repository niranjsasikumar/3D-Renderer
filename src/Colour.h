#ifndef COLOUR_H
#define COLOUR_H
#include "Vec3.h"

class Colour {
  private:
    float r, g, b;

    void validateRange(const float& value) const;
  
  public:
    Colour();
    Colour(float red, float green, float blue);
    Colour(const Vec3& vec);

    float getR() const;
    float getG() const;
    float getB() const;

    Vec3 operator+(const Colour& c2) const;
    Vec3 operator*(const float& s) const; // Scalar multiplication
};

#endif