#include "Renderer.hpp"
#include <vector>
#include <tuple>
#include <cmath>
#include <limits>
#include "Colour.hpp"
#include "Scene.hpp"
#include "Camera.hpp"
#include "Vec3.hpp"
#include "Sphere.hpp"
#include "Light.hpp"

Renderer::Renderer(
  const float& render_distance,
  const int& output_width,
  const int& output_height
) : render_distance(render_distance),
output_width(output_width),
output_height(output_height) {}

// Return the framebuffer created from the given scene
std::vector<Colour> Renderer::render(const Scene& scene) {
  int width = output_width;
  int height = output_height;
  
  Camera camera = scene.getCamera();

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

      framebuffer[j + i * width] = castRay(
        camera.getPosition(),
        direction,
        scene.getBackgroundColour(),
        scene.getAmbientLight(),
        scene.getSpheres(),
        scene.getLights(),
        0
      );
    }
  }

  return framebuffer;
}

/* Return the direction that a ray is reflected based on its initial direction
and the surface normal of the sphere it intersects with */
Vec3 reflect(const Vec3& direction, const Vec3& surface_normal) {
  return direction - surface_normal * (direction * surface_normal) * 2.0f;
}

// Return the colour at the point of intersection of a ray
Colour Renderer::castRay(
  const Vec3& origin,
  const Vec3& direction,
  const Colour& background_colour,
  const float& ambient_light,
  const std::vector<Sphere>& spheres,
  const std::vector<Light>& lights,
  const size_t depth
) {
  Sphere sphere;
  Vec3 point; // Point of intersection
  Vec3 surface_normal; // Surface normal at point of intersection

  bool intersects_sphere = sceneIntersection(
    origin, direction, spheres, point, surface_normal, sphere
  );

  /* Return the background colour if the ray does not intersect anything or if
  the ray is reflected too many times */
  if (depth > 5 || !intersects_sphere) return background_colour;
  
  Vec3 reflect_direction = reflect(direction, surface_normal).normalize();
  // Origin of reflection, offset to prevent intersection with object itself
  Vec3 reflect_origin = reflect_direction * surface_normal < 0
    ? point - surface_normal * 1e-3
    : point + surface_normal * 1e-3;
  
  Colour reflect_colour = castRay(
    reflect_origin,
    reflect_direction,
    background_colour,
    ambient_light,
    spheres,
    lights,
    depth + 1
  );

  float diffuse_light_intensity, specular_light_intensity;

  std::tie(
    diffuse_light_intensity, specular_light_intensity
  ) = getLightIntensities(
    direction, point, surface_normal, ambient_light, lights, spheres, sphere
  );

  Vec3 diffuse_colour = sphere.getColour()
    * diffuse_light_intensity
    * sphere.getDrc();
  
  Vec3 specular_colour = Colour(1.0f, 1.0f, 1.0f)
    * specular_light_intensity
    * sphere.getSrc();
  
  Vec3 reflection_colour = reflect_colour * sphere.getReflectivity();

  return Colour(diffuse_colour + specular_colour + reflection_colour);
}

// Returns the diffuse and specular light intensities at a point of intersection
std::tuple<float,float> Renderer::getLightIntensities(
  const Vec3& direction,
  const Vec3& intersection_point,
  const Vec3& surface_normal,
  const float& ambient_light,
  const std::vector<Light>& lights,
  const std::vector<Sphere>& spheres,
  const Sphere& sphere
) {
  float diffuse_light_intensity = ambient_light;
  float specular_light_intensity = ambient_light;

  for (size_t i = 0; i < lights.size(); i++) {
    Vec3 light_to_intersection = lights[i].getPosition() - intersection_point;
    Vec3 light_direction = light_to_intersection.normalize();
    float light_distance = light_to_intersection.norm();

    bool point_in_shadow = pointInShadow(
      light_direction,
      light_distance,
      intersection_point,
      surface_normal,
      spheres
    );

    // No effect from light source if point of intersection is in a shadow
    if (point_in_shadow) continue;

    diffuse_light_intensity += lights[i].getIntensity()
      * std::max(0.0f, light_direction * surface_normal);
    
    specular_light_intensity += powf(
      std::max(0.0f, reflect(light_direction, surface_normal) * direction),
      sphere.getSpecularExponent()
    ) * lights[i].getIntensity();
  }

  return std::tuple<float,float> (
    diffuse_light_intensity, specular_light_intensity
  );
}

// Returns whether a point of intersection is in the shadow of a light source
bool Renderer::pointInShadow(
  const Vec3& light_direction,
  const float& light_distance,
  const Vec3& point,
  const Vec3& surface_normal,
  const std::vector<Sphere>& spheres
) {
  // Origin of shadow ray, offset to prevent intersection with object itself
  Vec3 shadow_origin = light_direction * surface_normal < 0
    ? point - surface_normal * 1e-3
    : point + surface_normal * 1e-3;

  Vec3 shadow_point; // Point of intersection of shadow ray
  Vec3 shadow_sn; // Surface normal at point of intersection of shadow ray
  Sphere temp_sphere;

  bool shadow_ray_has_intersection = sceneIntersection(
    shadow_origin,
    light_direction,
    spheres,
    shadow_point,
    shadow_sn,
    temp_sphere
  );

  // Whether the point of intersection is in a shadow
  bool point_in_shadow = (
    (shadow_point - shadow_origin).norm() < light_distance
  );

  return shadow_ray_has_intersection && point_in_shadow;
}

/* Returns true if the ray with the given origin and direction intersects with
the given sphere and updates distance to distance from origin to first point of
intersection, if any */
bool raySphereIntersection(
  const Vec3& origin,
  const Vec3& direction,
  float& distance,
  const Sphere& sphere
) {
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

/* Returns true if the ray with the given origin and direction intersects with
any sphere and updates point, surface_normal and sphere to the intersected
sphere's values */
bool Renderer::sceneIntersection(
  const Vec3& origin,
  const Vec3& direction,
  const std::vector<Sphere>& spheres,
  Vec3& point,
  Vec3& surface_normal,
  Sphere& sphere
) {
  // Initialized with maximum possible representable distance to a sphere
  float sphere_distance = std::numeric_limits<float>::max();

  /* Update point of intersection, surface normal, and intersected sphere to
  that of the closest sphere */
  for (size_t i = 0; i < spheres.size(); i++) {
    float distance = 0.0f;
    bool intersects_sphere = raySphereIntersection(
      origin, direction, distance, spheres[i]
    );
    if (intersects_sphere && distance < sphere_distance) {
      sphere_distance = distance;
      point = origin + direction * distance;
      surface_normal = (point - spheres[i].getCenter()).normalize();
      sphere = spheres[i];
    }
  }

  // Only render spheres that are within 1000 units of the camera
  return sphere_distance < render_distance;
}