#ifndef MESH_H
#define MESH_H

#include "object.h"
#include "triangle.h"

class mesh : public object {

private:
  std::vector<shared_ptr<triangle>> triangles;
  shared_ptr<material> mat;
};

#endif
