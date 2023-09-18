#include "scenes.hpp"

Scene getScene1() {
  Colour background_colour(0.05, 0.05, 0.05);
  Camera camera(Vec3(0, 0, 0), 1, 1);
  Scene scene(background_colour, 0, camera);

  Sphere red_sphere(Vec3(0, 0, 5), 2, Colour(0.5, 0, 0), 0.9, 0.1, 10, 0);
  scene.addSphere(red_sphere);

  scene.addLight(Light(Vec3(-20, 20, -20), 2.0));

  return scene;
}