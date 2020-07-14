#pragma once
#include <materials/material.hpp>
#include <texture.hpp>

class Isotropic : public Material
{
public:
    std::shared_ptr<Texture> albedo;

    Isotropic(std::shared_ptr<Texture> tex) : albedo(tex) {}

    virtual bool scatter(
        const Ray &ray, const Hit &hit, color3 &attenuation, Ray &scattered) const
    {
        scattered = Ray(hit.pos, randomUnitSphere(), ray.time);
        attenuation = albedo->value(hit.u, hit.v, hit.pos);
        return true;
    }
};