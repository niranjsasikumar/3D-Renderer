#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "Colour.hpp"
#include "Camera.hpp"
#include "Light.hpp"
#include "Sphere.hpp"

class Scene {
  private:
    Colour background_colour;
    float ambient_light;
    Camera camera;
    std::vector<Light> lights;
    std::vector<Sphere> spheres;

  public:
    Scene(
      const Colour& background_colour,
      const float& ambient_light,
      const Camera& camera,
      const std::vector<Light>& lights,
      const std::vector<Sphere>& spheres
    );
    Scene(
      const Colour& background_colour,
      const float& ambient_light,
      const Camera& camera
    );

    Colour getBackgroundColour() const;
    float getAmbientLight() const;
    Camera getCamera() const;
    void addLight(const Light light);
    void addLights(const std::vector<Light>& new_lights);
    std::vector<Light> getLights() const;
    void addSphere(const Sphere sphere);
    void addSpheres(const std::vector<Sphere>& new_spheres);
    std::vector<Sphere> getSpheres() const;
};

#endif