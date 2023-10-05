# 3D Renderer
A program that generates images from three-dimensional scenes. Uses ray tracing-based rendering techniques to simulate the physical behaviour of light.

## Example

### Scene Creation

To generate an image, a scene must be created. A Scene object can be instantiated as shown below.

```cpp
Colour background_colour(0.05, 0.05, 0.05);
float ambient_light = 0.0;

Vec3 camera_position(0.0, 0.0, 0.0);
float fov = 1.0; // Field of view
float zoom = 1.0;
Camera camera(camera_position, fov, zoom);

Scene scene(background_colour, ambient_light, camera);
```

Once a scene is created, you can add spheres and light sources to the scene as shown below.

To add a sphere:
```cpp
Vec3 center(0.0, 0.0, 5.0);
float radius = 2.0;
Colour colour(0.5, 0.0, 0.0);
float drc = 0.9; // Diffuse reflection coefficient
float src = 0.1; // Specular reflection coefficient
float se = 10.0; // Specular exponent
float reflectivity = 0.0;
Sphere red_sphere(center, radius, colour, drc, src, se, reflectivity);

scene.addSphere(red_sphere);
```

To add a light source:
```cpp
Vec3 light_position(-20.0, 20.0, -20.0);
float intensity = 2.0;
Light light(light_position, intensity);

scene.addLight(light);
```

### Scene Rendering

Once you have a scene, you can render a framebuffer of the scene as shown below.

```cpp
float render_distance = 1000.0
int output_width = 800;
int output_height = 600;
Renderer renderer(render_distance, output_width, output_height);

std::vector<Colour> framebuffer = renderer.render(scene);
```

### Image Output

The created framebuffer can be saved as a file as shown below. The image file formats that are supported are: .pbm, .pgm, .ppm, .pnm

```cpp
std::string output_path = "./output.ppm";
saveFramebufferToFile(framebuffer, output_path, output_width, output_height);
```

### Result

The image generated from rendering the scene specified above will look like this:

![Red sphere with a black background](https://github.com/niranjsasikumar/3D-Renderer/raw/main/example/output/scene1.png)