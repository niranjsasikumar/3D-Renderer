#include <vector>
#include <fstream>
#include <cmath>
#include <limits>
#include "Camera.h"
#include "Vec3.h"
#include "Scene.h"
#include "Sphere.h"
#include "Colour.h"
#include "Light.h"

// Returns true if the ray with the given origin and direction intersects with the given sphere and updates distance to distance from origin to first point of intersection, if any
bool raySphereIntersection(const Vec3& origin, const Vec3& direction, float& distance, const Sphere& sphere) {
  // Vector from origin of ray to center of sphere
  Vec3 voc = sphere.getCenter() - origin;
  // Represents the projection of voc onto the ray
  float pvr = voc * direction;
  // Distance squared from point on ray closest to sphere center to center
  float d2 = voc * voc - pvr * pvr;
  // Radius squared
  float r2 = sphere.getRadius() * sphere.getRadius();

  if (d2 > r2)
    return false;
  
  // Distance from point on ray closest to sphere center to sphere surface
  float dcs = sqrtf(r2 - d2);
  // Update distance to distance from origin to first point of intersection
  distance = pvr - dcs;
  // Distance from origin to second point of intersection
  float distance2 = pvr + dcs;

  // No intersection if both points are behind the origin of the ray
  if (distance < 0.0f && distance2 < 0.0f)
    return false;
  
  return true;
}

// Returns true if the ray with the given origin and direction intersects with any sphere and updates point, surface_normal and sphere to the intersected sphere's values
bool sceneIntersection(const Vec3& origin, const Vec3& direction, const std::vector<Sphere>& spheres, Vec3& point, Vec3& surface_normal, Sphere& sphere) {
  // Initialized with maximum possible representable distance to a sphere
  float sphere_distance = std::numeric_limits<float>::max();

  // Update point of intersection, surface normal, and intersected sphere to that of the closest sphere
  for (size_t i = 0; i < spheres.size(); i++) {
    float distance = 0.0f;
    if (raySphereIntersection(origin, direction, distance, spheres[i]) && distance < sphere_distance) {
      sphere_distance = distance;
      point = origin + direction * distance;
      surface_normal = (point - spheres[i].getCenter()).normalize();
      sphere = spheres[i];
    }
  }

  // Only render spheres that are within 1000 units of the camera
  return sphere_distance < 1000.0f;
}

// Return the direction that a ray is reflected based on its initial direction and the surface_normal of the sphere it intersects with
Vec3 reflect(const Vec3& direction, const Vec3& surface_normal) {
  return direction - surface_normal * (direction * surface_normal) * 2.0f;
}

// Return the colour of the point of intersection of a ray cast from origin with a direction
Colour castRay(const Vec3& origin, const Vec3& direction, const std::vector<Sphere>& spheres, const std::vector<Light>& lights, const size_t depth = 0) {
  Sphere sphere;
  Vec3 point; // Point of intersection
  Vec3 surface_normal; // Surface normal at point of intersection

  // Return the background colour if the ray does not intersect anything or if the ray is reflected too many times
  if (depth > 5 || !sceneIntersection(origin, direction, spheres, point, surface_normal, sphere))
    return Colour(0.526, 0.804, 0.918);
  
  Vec3 reflect_direction = reflect(direction, surface_normal).normalize();
  // Origin of reflection, slightly offset to prevent intersection with object itself
  Vec3 reflect_origin = reflect_direction * surface_normal < 0 ? point - surface_normal * 1e-3 : point + surface_normal * 1e-3;
  Colour reflect_colour = castRay(reflect_origin, reflect_direction, spheres, lights, depth + 1);

  float diffuse_light_intensity = 0.0f, specular_light_intensity = 0.0f;

  for (size_t i = 0; i < lights.size(); i++) {
    Vec3 light_direction = (lights[i].getPosition() - point).normalize();
    float light_distance = (lights[i].getPosition() - point).norm();

    // Origin of shadow ray, slightly offset to prevent intersection with object itself
    Vec3 shadow_origin = light_direction * surface_normal < 0 ? point - surface_normal * 1e-3 : point + surface_normal * 1e-3;

    // Point of intersection of shadow ray
    Vec3 shadow_point;
    // Surface normal at point of intersection of shadow ray
    Vec3 shadow_sn;
    Sphere temp_sphere;

    // No effect from light source if point of intersection is in a shadow
    if (sceneIntersection(shadow_origin, light_direction, spheres, shadow_point, shadow_sn, temp_sphere) && (shadow_point - shadow_origin).norm() < light_distance)
      continue;

    diffuse_light_intensity += lights[i].getIntensity() * std::max(0.0f, light_direction * surface_normal);
    specular_light_intensity += powf(std::max(0.0f, reflect(light_direction, surface_normal) * direction), sphere.getSpecularExponent()) * lights[i].getIntensity();
  }

  return Colour(sphere.getColour() * diffuse_light_intensity * sphere.getDrc() + Colour(1.0f, 1.0f, 1.0f) * specular_light_intensity * sphere.getSrc() + reflect_colour * sphere.getReflectivity());
}

// Cast a ray from the camera in the direction of each pixel to get the colour of each pixel and output the rendered image
void render(const Scene& scene) {
  Camera camera = scene.getCamera();

  // Dimensions of output image
  int width = camera.getWidth();
  int height = camera.getHeight();

  // Field of view of camera
  float fov = camera.getFieldOfView();
  
  // Create framebuffer
  std::vector<Colour> framebuffer(width * height);
  for (size_t i = 0; i < height; i++) {
    for (size_t j = 0; j < width; j++) {
      // x and y directions of pixels relative to camera
      float x = (2 * (j + 0.5) / width - 1) * tan(fov / 2) * width / height;
      float y = - (2 * (i + 0.5) / height - 1) * tan(fov / 2);
      // Direction to cast ray
      Vec3 direction = Vec3(x, y, camera.getZoom()).normalize();
      framebuffer[j + i * width] = castRay(camera.getPosition(), direction, scene.getSpheres(), scene.getLights());
    }
  }

  // Save framebuffer to file
  std::ofstream out_image;
  out_image.open("../out_image.ppm");
  out_image << "P3\n" << width << " " << height << "\n255\n";
  for (size_t i = 0; i < height * width; i++) {
    int r = static_cast<int>(255 * framebuffer[i].getR());
    int g = static_cast<int>(255 * framebuffer[i].getG());
    int b = static_cast<int>(255 * framebuffer[i].getB());
    out_image << r << " " << g << " " << b << "\n";
  }
  out_image.close();
}

int main() {
  Camera camera(Vec3(0, 0, 0), 1, 800, 600, 1);

  Scene scene(camera);

  Sphere whiteSphere(Vec3(-2.5, -2, 12), 2, Colour(0.4, 0.4, 0.4), 0.6, 0.3, 50, 0.1);
  Sphere blueSphere(Vec3(2.5, -2, 19), 4, Colour(0.0, 0.0, 0.25), 0.9, 0.1, 10, 0.0);
  Sphere mirrorSphere(Vec3(-1, 3, 22), 4, Colour(1.0, 1.0, 1.0), 0.0, 1.0, 1000, 0.9);
  scene.addSpheres(std::vector<Sphere> { whiteSphere, blueSphere, mirrorSphere });

  scene.addLight(Light(Vec3(-20, 20, -20), 2.0));
  scene.addLight(Light(Vec3(30, 50, 20), 1.5));
  scene.addLight(Light(Vec3(30, 20, -30), 1.5));

  render(scene);

  return 0;
}