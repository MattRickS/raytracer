#pragma once
#include <materials/material.hpp>
#include <texture.hpp>

class DiffuseLight : public Material
{
public:
    std::shared_ptr<Texture> emit;

    DiffuseLight(std::shared_ptr<Texture> tex) : emit(tex) {}

    virtual bool scatter(
        const Ray &ray, const Hit &hit, color3 &attenuation, Ray &scattered) const
    {
        return false;
    }

    virtual color3 emitted(double u, double v, const point3 &pos) const
    {
        return emit->value(u, v, pos);
    }
};
