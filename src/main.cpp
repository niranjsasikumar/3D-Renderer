#include <vector>
#include <string>
#include <fstream>
#include "Renderer.h"

void saveFramebufferToFile(
  const std::vector<Colour>& framebuffer,
  const std::string& output_file_path,
  const int& output_width,
  const int& output_height
) {
  std::ofstream out_image;
  out_image.open(output_file_path);

  out_image << "P3\n" << output_width << " " << output_height << "\n255\n";

  for (size_t i = 0; i < output_width * output_height; i++) {
    int r = static_cast<int>(255 * framebuffer[i].getR());
    int g = static_cast<int>(255 * framebuffer[i].getG());
    int b = static_cast<int>(255 * framebuffer[i].getB());
    out_image << r << " " << g << " " << b << "\n";
  }

  out_image.close();
}

int main() {
  Colour background_colour(0.526, 0.804, 0.918);
  Camera camera(Vec3(0, 0, 0), 1, 1);
  Scene scene(background_colour, camera);

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

  int output_width = 800;
  int output_height = 600;
  Renderer renderer(1000, output_width, output_height);

  std::vector<Colour> framebuffer = renderer.render(scene);
  saveFramebufferToFile(
    framebuffer, "../out_image.ppm", output_width, output_height
  );

  return 0;
}