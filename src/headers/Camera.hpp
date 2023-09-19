#ifndef CAMERA_H
#define CAMERA_H
#include "Vec3.hpp"

class Camera {
  private:
    Vec3 position;
    float field_of_view;
    float zoom;

  public:
    Camera();
    Camera(const Vec3& position, const float& field_of_view, const float& zoom);

    Vec3 getPosition() const;
    float getFieldOfView() const;
    float getZoom() const;
};

#endif