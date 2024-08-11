#ifndef SPHERE_H
#define SPHERE_H

// #include "interval.h"
#include "aabb.h"
#include "material.h"
#include "object.h"
#include "util.h"
#include <cmath>
// #include "ray.h"
// #include "vector.h"
class sphere : public object {
public:
  // Stationary Sphere
  sphere(const point3 &center, double radius, shared_ptr<material> mat)
      : center1(center), radius(std::fmax(0, radius)), mat(mat),
        is_moving(false) {}

  // Moving Sphere
  sphere(const point3 &center1, const point3 &center2, double radius,
         shared_ptr<material> mat)
      : center1(center1), radius(std::fmax(0, radius)), mat(mat),
        is_moving(true) {
    center_vec = center2 - center1;
  }
  bool hit(const ray &r, interval ray_t, hit_record &rec) const override;
  aabb bounding_box() const override { return bbox; }

private:
  point3 center1;
  double radius;
  shared_ptr<material> mat;
  bool is_moving;
  vec3 center_vec;
  aabb bbox;

  static void get_sphere_uv(const point3 &p, double &u, double &v);
  point3 sphere_center(double time) const {
    // Linearly interpolate from center1 to center2 according to time, where t=0
    // yields center1, and t=1 yields center2.
    return center1 + time * center_vec;
  }
};

#endif
