#include "object.h"

void hit_record::set_face_normal(const ray &r, const vec3 &outward_normal) {
  auto d = dot(r.direction(), outward_normal);
  if (d > 0) {
    front_face = false;
    normal = -outward_normal;
  } else {
    front_face = true;
    normal = outward_normal;
  }
}
