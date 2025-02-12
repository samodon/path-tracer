#ifndef HITTABLE_H
#define HITTABLE_H
#include "aabb.h"
#include "interval.h"
#include "material.h"
#include "ray.h"
#include <memory>
class hit_record {
public:
  point3 p;
  point3 l_p;
  vec3 normal;
  double t;
  double u, v;
  std::shared_ptr<material> mat;
  bool front_face;

  void set_face_normal(const ray &r, const vec3 &outward_normal);
};

class object {
public:
  inline virtual ~object() = default;
  virtual bool hit(const ray &r, interval ray_t, hit_record &rec) const = 0;

  virtual aabb bounding_box() const = 0;
};

#endif
