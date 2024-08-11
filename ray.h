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
class ray {
public:
  ray() {}

  ray(const point3 &origin, const vec3 &direction, double time)
      : orig(origin), dir(direction), tm(time) {}

  ray(const point3 &origin, const vec3 &direction)
      : ray(origin, direction, 0) {}

  const point3 &origin() const { return orig; }
  const vec3 &direction() const { return dir; }

  double time() const { return tm; }

  point3 at(double t) const { return orig + t * dir; }

private:
  point3 orig;
  vec3 dir;
  double tm;
};
#endif
