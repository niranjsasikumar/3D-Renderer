#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "Colour.h"
#include "Camera.h"
#include "Light.h"
#include "Sphere.h"

class Scene {
  private:
    Colour background_colour;
    Camera camera;
    std::vector<Light> lights;
    std::vector<Sphere> spheres;

  public:
    Scene(
      const Colour& background_colour,
      const Camera& camera,
      const std::vector<Light>& lights,
      const std::vector<Sphere>& spheres
    );
    Scene(const Colour& background_colour, const Camera& camera);

    Colour getBackgroundColour() const;
    Camera getCamera() const;
    void addLight(const Light light);
    void addLights(const std::vector<Light>& new_lights);
    std::vector<Light> getLights() const;
    void addSphere(const Sphere sphere);
    void addSpheres(const std::vector<Sphere>& new_spheres);
    std::vector<Sphere> getSpheres() const;
};

#endif