#include "scenes.hpp"

Scene getScene3() {
  Colour background_colour(0.529, 0.808, 0.922);
  Camera camera(Vec3(0, 0, 0), 1, 1);
  Scene scene(background_colour, 0, camera);

  Sphere white_sphere(
    Vec3(-2.5, -2, 12), 2, Colour(0.4, 0.4, 0.4), 0.6, 0.3, 50, 0.1
  );
  Sphere blue_sphere(
    Vec3(2.5, -2, 19), 4, Colour(0.0, 0.0, 0.25), 0.9, 0.1, 10, 0.0
  );
  Sphere mirror_sphere(
    Vec3(-1, 3, 22), 4, Colour(1.0, 1.0, 1.0), 0.0, 1.0, 1000, 0.9
  );
  scene.addSpheres(
    std::vector<Sphere> { white_sphere, blue_sphere, mirror_sphere }
  );

  scene.addLight(Light(Vec3(-20, 20, -20), 2.0));
  scene.addLight(Light(Vec3(30, 50, 20), 1.5));
  scene.addLight(Light(Vec3(30, 20, -30), 1.5));

  return scene;
}