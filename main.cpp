#include "camera.h"
#include "material.h"
#include "object_list.h"
#include "sphere.h"
int main() {
  object_list world;

  // Ground
  auto ground_material = make_shared<lambertian>(color(0.5, 0.5, 0.5));
  world.add(make_shared<sphere>(point3(0, -100.5, -1), 100, ground_material));

  // Lambertian sphere
  auto lambertian_material = make_shared<lambertian>(color(0.1, 0.2, 0.5));
  world.add(make_shared<sphere>(point3(-1, 0, -1), 0.5, lambertian_material));

  // Metal sphere
  auto metal_material = make_shared<metal>(color(0.8, 0.6, 0.2), 0.0);
  world.add(make_shared<sphere>(point3(0, 0, -1), 0.5, metal_material));

  // Glass sphere
  auto glass_material = make_shared<dielectric>(1.5);
  world.add(make_shared<sphere>(point3(1, 0, -1), 0.5, glass_material));

  camera cam;
  cam.aspect_ratio = 16.0 / 9.0;
  cam.image_width = 1000;
  cam.samples_per_pixel = 200;
  cam.max_depth = 50;
  cam.vfov = 30;
  cam.lookfrom = point3(0, 0, 3);
  cam.lookat = point3(0, 0, -1);
  cam.vup = vec3(0, 1, 0);
  cam.defocus_angle = 0.0;
  cam.focus_dist = 1.0;
  cam.render(world);
}
