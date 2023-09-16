#ifndef CAMERA_H
#define CAMERA_H
#include "Vec3.h"

class Camera {
  private:
    Vec3 position;
    float fieldOfView;
    int width;
    int height;
    float zoom;

  public:
    Camera(
      const Vec3& position,
      const float& fieldOfView,
      const int& width,
      const int& height,
      const float& zoom
    );

    Vec3 getPosition() const;
    float getFieldOfView() const;
    int getWidth() const;
    int getHeight() const;
    float getZoom() const;
};

#endif