#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "object.h"

class triangle : public object {
public:
  triangle(const point3 &v0, const point3 &v1, const point3 &v2,
           shared_ptr<material> mat)
      : v0(v0), v1(v1), v2(v2), mat(mat) {
    normal = unit_vector(cross(v1 - v0, v2 - v0));
    D = dot(normal, v0);
  }

  virtual bool hit(const ray &r, interval ray_t,
                   hit_record &rec) const override {
    auto denom = dot(normal, r.direction());

    if (std::fabs(denom) < 1e-8)
      return false;

    auto t = (D - dot(normal, r.origin())) / denom;
    if (!ray_t.contains(t))
      return false;

    point3 P = r.at(t);

    vec3 edge0 = v1 - v0;
    vec3 edge1 = v2 - v1;
    vec3 edge2 = v0 - v2;

    vec3 C0 = P - v0;
    vec3 C1 = P - v1;
    vec3 C2 = P - v2;

    if (dot(normal, cross(edge0, C0)) < 0)
      return false;
    if (dot(normal, cross(edge1, C1)) < 0)
      return false;
    if (dot(normal, cross(edge2, C2)) < 0)
      return false;

    rec.t = t;
    rec.p = P;
    rec.mat = mat;
    rec.set_face_normal(r, normal);

    return true;
  }

  virtual void set_bounding_box() {
    auto min_point = point3(std::fmin(v0.x(), std::fmin(v1.x(), v2.x())),
                            std::fmin(v0.y(), std::fmin(v1.y(), v2.y())),
                            std::fmin(v0.z(), std::fmin(v1.z(), v2.z())));

    auto max_point = point3(std::fmax(v0.x(), std::fmax(v1.x(), v2.x())),
                            std::fmax(v0.y(), std::fmax(v1.y(), v2.y())),
                            std::fmax(v0.z(), std::fmax(v1.z(), v2.z())));

    bbox = aabb(min_point, max_point);
  }

  aabb bounding_box() const override { return bbox; }

private:
  point3 v0, v1, v2;
  vec3 normal;
  shared_ptr<material> mat;
  aabb bbox;
  double D;
};
#endif
