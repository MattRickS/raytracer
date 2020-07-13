#pragma once
#include <materials/material.hpp>
#include <ray.hpp>
#include <texture.hpp>
#include <vec3.hpp>

class Lambertian : public Material
{
public:
    std::shared_ptr<Texture> albedo;

    Lambertian(std::shared_ptr<Texture> tex) : albedo(tex) {}

    virtual bool scatter(
        const Ray &ray, const Hit &hit, color3 &attenuation, Ray &scattered) const
    {
        vec3 scatter_direction = hit.normal + randomUnitVector();
        scattered = Ray(hit.pos, scatter_direction, ray.time);
        attenuation = albedo->value(hit.u, hit.v, hit.pos);
        return true;
    }
};