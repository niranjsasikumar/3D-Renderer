#include "Scene.h"

Scene::Scene(
  const Colour& backgroundColour,
  const Camera& camera,
  const std::vector<Light>& lights,
  const std::vector<Sphere>& spheres
) : backgroundColour(backgroundColour),
camera(camera),
lights(lights),
spheres(spheres) {}

Scene::Scene(const Colour& backgroundColour, const Camera& camera) : Scene(
  backgroundColour, camera, std::vector<Light>(), std::vector<Sphere>()
) {}

Colour Scene::getBackgroundColour() const { return backgroundColour; }

Camera Scene::getCamera() const { return camera; }

void Scene::addLight(const Light light) { lights.push_back(light); }

void Scene::addLights(const std::vector<Light>& newLights) {
  lights.insert(lights.end(), newLights.begin(), newLights.end());
}

std::vector<Light> Scene::getLights() const { return lights; }

void Scene::addSphere(const Sphere sphere) { spheres.push_back(sphere); }

void Scene::addSpheres(const std::vector<Sphere>& newSpheres) {
  spheres.insert(spheres.end(), newSpheres.begin(), newSpheres.end());
}

std::vector<Sphere> Scene::getSpheres() const { return spheres; }