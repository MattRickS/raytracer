#pragma once
#include <hittables/hittable.hpp>
#include <ray.hpp>
#include <vec3.hpp>

class Material
{
public:
    virtual bool scatter(
        const Ray &ray, const Hit &hit, color3 &attenuation, Ray &scattered) const = 0;
};
