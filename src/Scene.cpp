#include "Scene.hpp"

Scene::Scene(
  const Colour& background_colour,
  const Camera& camera,
  const std::vector<Light>& lights,
  const std::vector<Sphere>& spheres
) : background_colour(background_colour),
camera(camera),
lights(lights),
spheres(spheres) {}

Scene::Scene(const Colour& background_colour, const Camera& camera) : Scene(
  background_colour, camera, std::vector<Light>(), std::vector<Sphere>()
) {}

Colour Scene::getBackgroundColour() const { return background_colour; }

Camera Scene::getCamera() const { return camera; }

void Scene::addLight(const Light light) { lights.push_back(light); }

void Scene::addLights(const std::vector<Light>& new_lights) {
  lights.insert(lights.end(), new_lights.begin(), new_lights.end());
}

std::vector<Light> Scene::getLights() const { return lights; }

void Scene::addSphere(const Sphere sphere) { spheres.push_back(sphere); }

void Scene::addSpheres(const std::vector<Sphere>& new_spheres) {
  spheres.insert(spheres.end(), new_spheres.begin(), new_spheres.end());
}

std::vector<Sphere> Scene::getSpheres() const { return spheres; }