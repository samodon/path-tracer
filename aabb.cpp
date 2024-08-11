#include "aabb.h"
aabb aabb::universe;
aabb aabb::empty;
const interval &aabb::axis_interval(int n) const {
  if (n == 1)
    return y;
  if (n == 2)
    return z;
  return x;
}

bool aabb::hit(const ray &r, interval ray_t) const {
  const point3 &ray_orig = r.origin();
  const vec3 &ray_dir = r.direction();

  for (int axis = 0; axis < 3; axis++) {
    const interval &ax = axis_interval(axis);
    const double adinv = 1.0 / ray_dir[axis];

    auto t0 = (ax.min - ray_orig[axis]) * adinv;
    auto t1 = (ax.max - ray_orig[axis]) * adinv;

    if (t0 < t1) {
      if (t0 > ray_t.min)
        ray_t.min = t0;
      if (t1 < ray_t.max)
        ray_t.max = t1;
    } else {
      if (t1 > ray_t.min)
        ray_t.min = t1;
      if (t0 < ray_t.max)
        ray_t.max = t0;
    }

    if (ray_t.max <= ray_t.min)
      return false;
  }
  return true;
}

void aabb::pad_to_minimums() {
  // Adjust the AABB so that no side is narrower than some delta, padding if
  // necessary.

  double delta = 0.0001;
  if (x.size() < delta)
    x = x.expand(delta);
  if (y.size() < delta)
    y = y.expand(delta);
  if (z.size() < delta)
    z = z.expand(delta);
}
