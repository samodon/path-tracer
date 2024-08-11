#include "material.h"
#include "object.h"
#include "util.h"
#include "vector.h"
#include <cmath>

bool material::scatter(const ray &r_in, const hit_record &rec,
                       color &attenuation, ray &scattered) const {
  return false;
}

bool lambertian::scatter(const ray &r_in, const hit_record &rec,
                         color &attenuation, ray &scattered) const {
  auto scatter_direction = rec.normal + random_unit_vector();
  // Catch degenerate scatter direction
  if (scatter_direction.near_zero()) {
    scatter_direction = rec.normal;
  }
  scattered = ray(rec.p, scatter_direction, r_in.time());
  attenuation = tex->value(rec.u, rec.v, rec.p);
  return true;
}
bool metal::scatter(const ray &r_in, const hit_record &rec, color &attenuation,
                    ray &scattered) const {
  vec3 reflected = reflect(r_in.direction(), rec.normal);
  reflected = unit_vector(reflected) + (fuzz * random_unit_vector());
  scattered = ray(rec.p, reflected, r_in.time());
  attenuation = albedo;
  return (dot(scattered.direction(), rec.normal) > 0);
}
bool dielectric::scatter(const ray &r_in, const hit_record &rec,
                         color &attenuation, ray &scattered) const {
  attenuation = color(1.0, 1.0, 1.0);
  double ri = rec.front_face ? (1.0 / refraction_index) : refraction_index;

  vec3 unit_direction = unit_vector(r_in.direction());
  double cos_theta = std::fmin(dot(-unit_direction, rec.normal), 1.0);
  double sin_theta = std::sqrt(1.0 - cos_theta * cos_theta);

  bool cannot_refract = ri * sin_theta > 1.0;
  vec3 direction;

  if (cannot_refract)
    direction = reflect(unit_direction, rec.normal);
  else
    direction = refract(unit_direction, rec.normal, ri);
  scattered = ray(rec.p, direction, r_in.time());
  return true;
}
double dielectric::reflectance(double cosine, double refraction_index) {
  // Use Schlick's approximation for reflectance.
  auto r0 = (1 - refraction_index) / (1 + refraction_index);
  r0 = r0 * r0;
  return r0 + (1 - r0) * std::pow((1 - cosine), 5);
}

double reflectance(double cosine, double refraction_index) {
  // Use Schlick's approximation for reflectance.
  auto r0 = (1 - refraction_index) / (1 + refraction_index);
  r0 = r0 * r0;
  return r0 + (1 - r0) * std::pow((1 - cosine), 5);
}

bool bsdf::scatter(const ray &r_in, color &intensity, const hit_record &rec,
                   color &attenuation, ray &scattered) const {
  // Compute the direction to the light source
  auto l_dir = rec.l_p - rec.p;
  auto l_dir_norm = unit_vector(l_dir); // Normalize light direction

  // Compute the half-vector
  auto half_vector = unit_vector(r_in.direction() + l_dir_norm);

  // Compute geometry term
  double G = geometry_term(rec.normal, r_in.direction(), l_dir_norm);

  // Compute distribution term
  double D = ggx_distribute(rec.normal, r_in.direction(), l_dir_norm);

  // Compute Fresnel term using Schlick's approximation
  double F =
      reflectance(dot(half_vector, r_in.direction()), index_of_refraction);

  // Calculate the specular term
  double cos_theta_r = std::max(0.0, dot(rec.normal, r_in.direction()));
  double cos_theta_l = std::max(0.0, dot(rec.normal, l_dir_norm));

  // Specular term using BRDF equation
  double specular = (D * G * F) / (4 * cos_theta_r * cos_theta_l);

  // Set attenuation to color of the material
  attenuation = albedo;

  // The scattered ray will be reflected (specular case), you can modify this
  // based on your scattering model
  vec3 reflected = reflect(r_in.direction(), rec.normal);
  scattered = ray(rec.p, reflected, r_in.time());

  // Apply attenuation to intensity (assuming this is what you need)
  intensity = attenuation * specular;

  return true;
}
double bsdf::ggx_distribute(const vec3 &normal, const vec3 &r_dir,
                            const vec3 &l_dir) const {
  auto half_dir = unit_vector(l_dir + r_dir);
  auto d = dot(half_dir, normal);
  auto rough2 = roughness * roughness;
  auto denom = M_PI * (pow((d * d) * (rough2 - 1) + 1, 2));
  return rough2 / denom;
}

double bsdf::geometry_term(const vec3 &normal, const vec3 &r_dir,
                           const vec3 &l_dir) const {
  // Compute the half-vector
  vec3 half_vector = unit_vector(r_dir + l_dir);

  // Lambda function to calculate the geometric attenuation factor G1
  auto G1 = [](const vec3 &normal, const vec3 &direction, double roughness) {
    double dot_product = dot(normal, direction);
    double a = roughness;
    double tan_theta = sqrt(1.0 / (dot_product * dot_product) - 1.0);
    double denom = 1.0 + sqrt(1.0 + a * a * tan_theta * tan_theta);
    return 2.0 * dot_product / denom;
  };

  // Calculate G1 for both directions
  double G1_r_dir = G1(normal, r_dir, roughness);
  double G1_l_dir = G1(normal, l_dir, roughness);

  // Compute the geometric term G
  double dot_normal_r_dir = dot(normal, r_dir);
  double dot_normal_l_dir = dot(normal, l_dir);

  // Ensure the terms are valid (i.e., directions are pointing towards the
  // surface)
  if (dot_normal_r_dir <= 0.0 || dot_normal_l_dir <= 0.0)
    return 0.0;

  return (G1_r_dir * G1_l_dir) / (4.0 * dot_normal_r_dir * dot_normal_l_dir);
}
