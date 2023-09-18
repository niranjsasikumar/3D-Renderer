#ifndef SPHERE_H
#define SPHERE_H
#include "Vec3.h"
#include "Colour.h"
#include <string>

class Sphere {
  private:
    Vec3 center;
    float radius;
    Colour colour;
    float drc; // Diffuse reflection coefficient
    float src; // Specular reflection coefficient
    float specular_exponent;
    float reflectivity;

  public:
    Sphere();
    Sphere(
      Vec3 center,
      float radius,
      Colour colour,
      float drc,
      float src,
      float specular_exponent,
      float reflectivity
    );

    Vec3 getCenter() const;
    float getRadius() const;
    Colour getColour() const;
    float getDrc() const;
    float getSrc() const;
    float getSpecularExponent() const;
    float getReflectivity() const;
};

#endif