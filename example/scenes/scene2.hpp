#include "Scene.hpp"

Scene getScene2() {
  Colour background_colour(0.8, 0.8, 0.8);
  Camera camera(Vec3(0, 0, 0), 1, 1);
  Scene scene(background_colour, 0.2, camera);

  Sphere o_atom(Vec3(0, 0, 7), 2, Colour(0.5, 0, 0), 0.9, 0.1, 10, 0);
  Sphere h_atom1(
    Vec3(-1.7, 1, 6.5), 1.2, Colour(0.5, 0.5, 0.5), 0.9, 0.1, 10, 0
  );
  Sphere h_atom2(
    Vec3(1.7, 1, 6.5), 1.2, Colour(0.5, 0.5, 0.5), 0.9, 0.1, 10, 0
  );
  scene.addSpheres(
    std::vector<Sphere> { o_atom, h_atom1, h_atom2 }
  );

  scene.addLight(Light(Vec3(-20, 20, -20), 1.2));
  scene.addLight(Light(Vec3(15, 0, -20), 1.2));

  return scene;
}