#include "vector.h"

// Default Constructor
vec3::vec3() : e{0, 0, 0} {}

// Constructor with parameters
vec3::vec3(double e0, double e1, double e2) : e{e0, e1, e2} {}

// Accessor functions
double vec3::x() const { return e[0]; }
double vec3::y() const { return e[1]; }
double vec3::z() const { return e[2]; }

// Unary minus operator
vec3 vec3::operator-() const { return vec3(-e[0], -e[1], -e[2]); }

// Subscript operator (const)
double vec3::operator[](int i) const { return e[i]; }

// Subscript operator (non-const)
double &vec3::operator[](int i) { return e[i]; }

// Addition assignment operator
vec3 &vec3::operator+=(const vec3 &v) {
  e[0] += v.e[0];
  e[1] += v.e[1];
  e[2] += v.e[2];
  return *this;
}

// Scalar multiplication assignment operator
vec3 &vec3::operator*=(double t) {
  e[0] *= t;
  e[1] *= t;
  e[2] *= t;
  return *this;
}

// Scalar division assignment operator
vec3 &vec3::operator/=(double t) { return *this *= 1 / t; }

// Calculate length of the vector
double vec3::length() const { return std::sqrt(length_squared()); }

// Calculate squared length of the vector
double vec3::length_squared() const {
  return e[0] * e[0] + e[1] * e[1] + e[2] * e[2];
}

// Output stream operator
std::ostream &operator<<(std::ostream &out, const vec3 &v) {
  return out << v.e[0] << ' ' << v.e[1] << ' ' << v.e[2];
}

// Addition operator
vec3 operator+(const vec3 &u, const vec3 &v) {
  return vec3(u.e[0] + v.e[0], u.e[1] + v.e[1], u.e[2] + v.e[2]);
}

// Subtraction operator
vec3 operator-(const vec3 &u, const vec3 &v) {
  return vec3(u.e[0] - v.e[0], u.e[1] - v.e[1], u.e[2] - v.e[2]);
}

// Element-wise multiplication operator
vec3 operator*(const vec3 &u, const vec3 &v) {
  return vec3(u.e[0] * v.e[0], u.e[1] * v.e[1], u.e[2] * v.e[2]);
}

// Scalar multiplication by a vector (right side)
vec3 operator*(double t, const vec3 &v) {
  return vec3(t * v.e[0], t * v.e[1], t * v.e[2]);
}

// Scalar multiplication by a vector (left side)
vec3 operator*(const vec3 &v, double t) { return t * v; }

// Scalar division
vec3 operator/(const vec3 &v, double t) { return (1 / t) * v; }

// Dot product
double dot(const vec3 &u, const vec3 &v) {
  return u.e[0] * v.e[0] + u.e[1] * v.e[1] + u.e[2] * v.e[2];
}

// Cross product
vec3 cross(const vec3 &u, const vec3 &v) {
  return vec3(u.e[1] * v.e[2] - u.e[2] * v.e[1],
              u.e[2] * v.e[0] - u.e[0] * v.e[2],
              u.e[0] * v.e[1] - u.e[1] * v.e[0]);
}
// Normalize the vector
vec3 unit_vector(const vec3 &v) { return v / v.length(); }

// Random number
vec3 vec3::random() {
  return vec3(random_double(), random_double(), random_double());
}

vec3 vec3::random(double min, double max) {
  return vec3(random_double(min, max), random_double(min, max),
              random_double(min, max));
}

bool vec3::near_zero() {
  auto s = 1e-8;
  return (std::fabs(e[0]) < s) && (std::fabs(e[1]) < s) &&
         (std::fabs(e[2]) < s);
}
