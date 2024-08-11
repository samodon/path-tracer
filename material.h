#ifndef MATERIAL_H
#define MATERIAL_H
#include "color.h"
#include "ray.h"
#include "texture.h"
class hit_record;

class material {
public:
  virtual ~material() = default;
  virtual color emitted(double u, double v, const point3 &p) const {
    return color(0, 0, 0);
  }
  virtual bool scatter(const ray &r_in, const hit_record &rec,
                       color &attenuation, ray &scattered) const;
};

class lambertian : public material {
public:
  // lambertian(const color &albedo) : albedo(albedo) {}
  lambertian(const color &albedo) : tex(make_shared<solid_color>(albedo)) {}
  lambertian(shared_ptr<texture> tex) : tex(tex) {}
  bool scatter(const ray &r_in, const hit_record &rec, color &attenuation,
               ray &scattered) const override;

private:
  color albedo;
  shared_ptr<texture> tex;
};

class bsdf : public material {
public:
  bsdf(const color &albedo, double metalness, double ior, double specular)
      : albedo(albedo), metalness(metalness), index_of_refraction(ior),
        roughness(specular) {}

  bool scatter(const ray &r_in, color &intensity, const hit_record &rec,
               color &attenuation, ray &scattered) const;

  double geometry_term(const vec3 &normal, const vec3 &r_dir,
                       const vec3 &l_dir) const;

private:
  color albedo;
  double roughness;
  double metalness;
  double index_of_refraction;

  double ggx_distribute(const vec3 &normal, const vec3 &r_dir,
                        const vec3 &l_dir) const;
};
class metal : public material {
public:
  metal(const color &albedo, double fuzz)
      : albedo(albedo), fuzz(fuzz < 1 ? fuzz : 1) {}
  bool scatter(const ray &r_in, const hit_record &rec, color &attenuation,
               ray &scattered) const override;

  double geometry_term(const vec3 &normal, const vec3 &r_dir,
                       const vec3 &l_dir) const;

private:
  color albedo;
  double fuzz;
};
class dielectric : public material {
public:
  dielectric(double refraction_index) : refraction_index(refraction_index) {}

  bool scatter(const ray &r_in, const hit_record &rec, color &attenuation,
               ray &scattered) const override;

private:
  // Refractive index in vacuum or air, or the ratio of the material's
  // refractive index over the refractive index of the enclosing media
  double refraction_index;
  static double reflectance(double cosine, double refraction_index);
};
class diffuse_light : public material {
public:
  diffuse_light(shared_ptr<texture> tex) : tex(tex) {}
  diffuse_light(const color &emit) : tex(make_shared<solid_color>(emit)) {}

  color emitted(double u, double v, const point3 &p) const override {
    return tex->value(u, v, p);
  }

private:
  shared_ptr<texture> tex;
};
#endif
