#include "Camera.h"

Camera::Camera(
  const Vec3& position,
  const float& field_of_view,
  const float& zoom
) : position(position), field_of_view(field_of_view), zoom(zoom) {}

Vec3 Camera::getPosition() const { return position; }

float Camera::getFieldOfView() const { return field_of_view; }

float Camera::getZoom() const { return zoom; }