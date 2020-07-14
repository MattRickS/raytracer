#pragma once
#include <hittables/hittable.hpp>
#include <ray.hpp>
#include <vec3.hpp>

class Material
{
public:
    virtual color3 emitted(double u, double v, const point3 &pos) const
    {
        return color3(0);
    }

    virtual bool scatter(
        const Ray &ray, const Hit &hit, color3 &attenuation, Ray &scattered) const = 0;
};
