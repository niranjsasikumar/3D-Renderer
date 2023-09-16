#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "Camera.h"
#include "Light.h"
#include "Sphere.h"

class Scene {
  private:
    Camera camera;
    std::vector<Light> lights;
    std::vector<Sphere> spheres;

  public:
    Scene(const Camera camera);
    Scene(const Camera camera, const std::vector<Light>& lights, const std::vector<Sphere>& spheres);

    Camera getCamera() const;
    void addLight(const Light light);
    void addLights(const std::vector<Light>& newLights);
    std::vector<Light> getLights() const;
    void addSphere(const Sphere sphere);
    void addSpheres(const std::vector<Sphere>& spheres);
    std::vector<Sphere> getSpheres() const;
};

#endif