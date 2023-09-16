#include "Camera.h"

Camera::Camera(
  const Vec3& position,
  const float& fieldOfView,
  const int& width,
  const int& height,
  const float& zoom
) : position(position),
fieldOfView(fieldOfView),
width(width),
height(height),
zoom(zoom) {}

Vec3 Camera::getPosition() const { return position; }

float Camera::getFieldOfView() const { return fieldOfView; }

int Camera::getWidth() const { return width; }

int Camera::getHeight() const { return height; }

float Camera::getZoom() const { return zoom; }