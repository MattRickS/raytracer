#pragma once
#include <materials/material.hpp>

double schlick(double cosine, double refractIndex)
{
    double r0 = (1 - refractIndex) / (1 + refractIndex);
    r0 *= r0;
    return r0 + (1 - r0) * pow((1 - cosine), 5);
}

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
            scattered = Ray(hit.pos, reflected, ray.time);
            return true;
        }
        double reflect_prob = schlick(cos_theta, etai_over_etat);
        if (randDouble() < reflect_prob)
        {
            vec3 reflected = reflect(dir, hit.normal);
            scattered = Ray(hit.pos, reflected, ray.time);
            return true;
        }

        vec3 refracted = refract(dir, hit.normal, etai_over_etat);
        scattered = Ray(hit.pos, refracted, ray.time);
        return true;
    }
};
