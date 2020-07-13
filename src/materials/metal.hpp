#pragma once
#include <materials/material.hpp>
#include <texture.hpp>
#include <vec3.hpp>

class Metal : public Material
{
public:
    std::shared_ptr<Texture> albedo;
    double fuzz;

    Metal(std::shared_ptr<Texture> tex, double fuzz) : albedo(tex), fuzz(fuzz < 1 ? fuzz : 1) {}

    virtual bool scatter(
        const Ray &ray, const Hit &hit, color3 &attenuation, Ray &scattered) const
    {
        vec3 reflected = reflect(normalise(ray.dir), hit.normal);
        scattered = Ray(hit.pos, reflected + fuzz * randomUnitSphere(), ray.time);
        attenuation = albedo->value(hit.u, hit.v, hit.pos);
        return (dot(scattered.dir, hit.normal) > 0);
    }
};
