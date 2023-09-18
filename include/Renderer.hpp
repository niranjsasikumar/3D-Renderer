#ifndef RENDERER_H
#define RENDERER_H
#include <vector>
#include <tuple>
#include "Colour.hpp"
#include "Scene.hpp"
#include "Vec3.hpp"
#include "Sphere.hpp"
#include "Light.hpp"

class Renderer {
  public:
    Renderer(
      const float& render_distance,
      const int& output_width,
      const int& output_height
    );
    std::vector<Colour> render(const Scene& scene);
  
  private:
    float render_distance;
    int output_width;
    int output_height;

    Colour castRay(
      const Vec3& origin,
      const Vec3& direction,
      const Colour& background_colour,
      const std::vector<Sphere>& spheres,
      const std::vector<Light>& lights,
      const size_t depth
    );
    std::tuple<float,float> getLightIntensities(
      const Vec3& direction,
      const Vec3& intersection_point,
      const Vec3& surface_normal,
      const std::vector<Light>& lights,
      const std::vector<Sphere>& spheres,
      const Sphere& sphere
    );
    bool pointInShadow(
      const Vec3& light_direction,
      const float& light_distance,
      const Vec3& point,
      const Vec3& surface_normal,
      const std::vector<Sphere>& spheres
    );
    bool sceneIntersection(
      const Vec3& origin,
      const Vec3& direction,
      const std::vector<Sphere>& spheres,
      Vec3& point,
      Vec3& surface_normal,
      Sphere& sphere
    );
};

#endif