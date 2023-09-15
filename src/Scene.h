#ifndef SCENE_H
#define SCENE_H
#include <vector>
#include "Vec3.h"
#include "Light.h"
#include "Sphere.h"

class Scene {
  private:
    Vec3 camera;
    std::vector<Light> lights;
    std::vector<Sphere> spheres;

  public:
    Scene();
    Scene(const Vec3 camera);
    Scene(const Vec3 camera, const std::vector<Light>& lights, const std::vector<Sphere>& spheres);

    Vec3 getCamera() const;
    void addLight(const Light light);
    void addLights(const std::vector<Light>& newLights);
    std::vector<Light> getLights() const;
    void addSphere(const Sphere sphere);
    void addSpheres(const std::vector<Sphere>& spheres);
    std::vector<Sphere> getSpheres() const;
};

#endif