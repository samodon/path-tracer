#ifndef OBJECT_LIST_H
#define OBJECT_LIST_H
#include "interval.h"
#include "object.h"
// #include "sphere.h"
// #include <memory>
// #include <vector>

using std::make_shared;
using std::shared_ptr;

class object_list : public object {
public:
  std::vector<shared_ptr<object>> objects;

  object_list() {}

  object_list(shared_ptr<object> object) { add(object); }

  inline void add(shared_ptr<object> object) { objects.push_back(object); }

  inline bool hit(const ray &r, interval ray_t,
                  hit_record &rec) const override {
    hit_record temp_rec;
    bool hit_anything = false;
    auto closest_so_far = ray_t.max;

    for (const auto &object : objects) {
      if (object->hit(r, interval(ray_t.min, closest_so_far), temp_rec)) {
        hit_anything = true;
        closest_so_far = temp_rec.t;
        rec = temp_rec;
      }
    }

    return hit_anything;
  }
};

#endif
