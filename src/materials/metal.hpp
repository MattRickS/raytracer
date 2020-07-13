#pragma once
#include <materials/material.hpp>
#include <vec3.hpp>

class Metal : public Material
{
public:
    color3 albedo;

    Metal(const color3 &col) : albedo(col) {}

    virtual bool scatter(
        const Ray &ray, const Hit &hit, color3 &attenuation, Ray &scattered) const
    {
        vec3 reflected = reflect(normalise(ray.dir), hit.normal);
        scattered = Ray(hit.pos, reflected);
        attenuation = albedo;
        return (dot(scattered.dir, hit.normal) > 0);
    }
};
