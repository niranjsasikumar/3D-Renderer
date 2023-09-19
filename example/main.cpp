#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include "scenes.hpp"
#include "Renderer.hpp"

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

int main(int argc, char* argv[]) {
  int output_width = 800;
  int output_height = 600;
  Renderer renderer(1000, output_width, output_height);

  Scene scene;
  try {
    scene = getScene(argc > 1 ? argv[1] : "scene1");
  } catch (...) {
    std::cout << "Invalid scene name";
    return -1;
  }

  std::vector<Colour> framebuffer = renderer.render(scene);
  std::string output_directory = argc > 2 ? argv[2] : ".";
  saveFramebufferToFile(
    framebuffer,
    output_directory + "/out_image.ppm",
    output_width,
    output_height
  );

  return 0;
}