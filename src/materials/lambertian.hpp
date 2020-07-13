#pragma once
#include <materials/material.hpp>
#include <ray.hpp>
#include <vec3.hpp>

class Lambertian : public Material
{
public:
    color3 albedo;

    Lambertian(const color3 &col) : albedo(col) {}

    virtual bool scatter(
        const Ray &ray, const Hit &hit, color3 &attenuation, Ray &scattered) const
    {
        vec3 scatter_direction = hit.normal + randomUnitVector();
        scattered = Ray(hit.pos, scatter_direction, ray.time);
        attenuation = albedo;
        return true;
    }
};