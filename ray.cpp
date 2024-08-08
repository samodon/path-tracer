#include "ray.h"
// #include "camera.h"
// #include "object.h"
// #include "pixel.h"
// #include "scene.h"

ray::ray(const point3 &o, const vec3 &d) : origin(o), direction(d) {}

ray::ray() {};

point3 ray::at(double t) const { return origin + direction * t; }
