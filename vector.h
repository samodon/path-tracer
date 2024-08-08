#ifndef VECTOR_H
#define VECTOR_H

#include "util.h"
#include <cmath>
#include <iostream>

class vec3 {
public:
  double e[3];

  vec3();
  vec3(double e0, double e1, double e2);

  double x() const;
  double y() const;
  double z() const;

  vec3 operator-() const;
  double operator[](int i) const;
  double &operator[](int i);

  vec3 &operator+=(const vec3 &v);
  vec3 &operator*=(double t);
  vec3 &operator/=(double t);

  double length() const;
  double length_squared() const;
  static vec3 random();
  static vec3 random(double min, double max);
  bool near_zero();
};
// point3 is just an alias for vec3, but useful for geometric clarity in the
// code.
using point3 = vec3;
// Vector Utility Functions
std::ostream &operator<<(std::ostream &out, const vec3 &v);
vec3 operator+(const vec3 &u, const vec3 &v);
vec3 operator-(const vec3 &u, const vec3 &v);
vec3 operator*(const vec3 &u, const vec3 &v);
vec3 operator*(double t, const vec3 &v);
vec3 operator*(const vec3 &v, double t);
vec3 operator/(const vec3 &v, double t);
double dot(const vec3 &u, const vec3 &v);
vec3 cross(const vec3 &u, const vec3 &v);
vec3 unit_vector(const vec3 &v);

inline vec3 random_in_unit_sphere() {
  while (true) {
    auto p = vec3::random(-1, 1);
    if (p.length_squared() < 1)
      return p;
  }
}
inline vec3 random_unit_vector() {
  return unit_vector(random_in_unit_sphere());
}
inline vec3 random_on_hemisphere(const vec3 &normal) {
  vec3 on_unit_sphere = random_unit_vector();
  if (dot(on_unit_sphere, normal) > 0.0) // In the same hemisphere as the normal
    return on_unit_sphere;
  else
    return -on_unit_sphere;
}
inline vec3 reflect(const vec3 &v, const vec3 &n) {
  return v - 2 * dot(v, n) * n;
}

inline vec3 refract(const vec3 &uv, const vec3 &n, double etai_over_etat) {
  auto cos_theta = std::fmin(dot(-uv, n), 1.0);
  vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
  vec3 r_out_parallel =
      -std::sqrt(std::fabs(1.0 - r_out_perp.length_squared())) * n;
  return r_out_perp + r_out_parallel;
}
inline vec3 unit_vector(const vec3 &v) { return v / v.length(); }

inline vec3 random_in_unit_disk() {
  while (true) {
    auto p = vec3(random_double(-1, 1), random_double(-1, 1), 0);
    if (p.length_squared() < 1)
      return p;
  }
}
#endif
