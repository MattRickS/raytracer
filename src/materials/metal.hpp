#pragma once
#include <materials/material.hpp>
#include <vec3.hpp>

class Metal : public Material
{
public:
    color3 albedo;
    double fuzz;

    Metal(const color3 &col, double fuzz) : albedo(col), fuzz(fuzz < 1 ? fuzz : 1) {}

    virtual bool scatter(
        const Ray &ray, const Hit &hit, color3 &attenuation, Ray &scattered) const
    {
        vec3 reflected = reflect(normalise(ray.dir), hit.normal);
        scattered = Ray(hit.pos, reflected + fuzz * randomUnitSphere());
        attenuation = albedo;
        return (dot(scattered.dir, hit.normal) > 0);
    }
};
