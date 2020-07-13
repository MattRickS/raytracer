#pragma once
#include <materials/material.hpp>

class Dielectric : public Material
{
public:
    double refractIndex;

    Dielectric(double refractIndex) : refractIndex(refractIndex) {}

    virtual bool scatter(
        const Ray &ray, const Hit &hit, color3 &attenuation, Ray &scattered) const
    {
        attenuation = color3(1.0);
        double etai_over_etat = (hit.front_face) ? (1.0 / refractIndex) : refractIndex;

        vec3 dir = normalise(ray.dir);
        double cos_theta = fmin(dot(-dir, hit.normal), 1.0);
        double sin_theta = sqrt(1.0 - cos_theta * cos_theta);
        if (etai_over_etat * sin_theta > 1.0)
        {
            vec3 reflected = reflect(dir, hit.normal);
            scattered = Ray(hit.pos, reflected);
            return true;
        }

        vec3 refracted = refract(dir, hit.normal, etai_over_etat);
        scattered = Ray(hit.pos, refracted);
        return true;
    }
};
