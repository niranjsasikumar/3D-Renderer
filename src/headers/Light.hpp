#ifndef LIGHT_H
#define LIGHT_H
#include "Vec3.hpp"

class Light {
  private:
    Vec3 position;
    float intensity;

  public:
    Light(Vec3 position, float intensity);

    Vec3 getPosition() const;
    float getIntensity() const;
};

#endif