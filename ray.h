#ifndef RAYTRACING_H
#define RAYTRACING_H
#include "vector.h"
// Define the Light structure
struct Light {
  point3 origin;
  vec3 direction;
  double luminosity;
  vec3 color;
  Light(const point3 &o, const vec3 &d, const double l, const vec3 c);
};

// Define the Ray structure
struct ray {
  point3 origin;
  vec3 direction;
  ray();
  ray(const point3 &o, const vec3 &d);
  point3 at(double t) const;
};
#endif
