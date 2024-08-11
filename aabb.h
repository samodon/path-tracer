#ifndef AABB_H
#define AABB_H

#include "interval.h"
#include "ray.h"
#include "vector.h"

class aabb {
public:
  interval x, y, z;
  static aabb universe;
  static aabb empty;
  aabb() {}
  aabb(const interval &x, const interval &y, const interval &z)
      : x(x), y(y), z(z) {
    pad_to_minimums();
  }

  aabb(const point3 &a, const point3 &b) {
    // Treat the two points a and b as extrema for the bounding box, so we don't
    // require a particular minimum/maximum coordinate order.

    x = (a[0] <= b[0]) ? interval(a[0], b[0]) : interval(b[0], a[0]);
    y = (a[1] <= b[1]) ? interval(a[1], b[1]) : interval(b[1], a[1]);
    z = (a[2] <= b[2]) ? interval(a[2], b[2]) : interval(b[2], a[2]);
    pad_to_minimums();
  }
  int longest_axis() const {
    // Returns the index of the longest axis of the bounding box.

    if (x.size() > y.size())
      return x.size() > z.size() ? 0 : 2;
    else
      return y.size() > z.size() ? 1 : 2;
  }

  aabb(const aabb &box0, const aabb &box1) {
    x = interval(box0.x, box1.x);
    y = interval(box0.y, box1.y);
    z = interval(box0.z, box1.z);
  }

  const interval &axis_interval(int n) const;

  bool hit(const ray &r, interval ray_t) const;

private:
  void pad_to_minimums();
};

#endif
