#pragma once
#include <hittable.hpp>
#include <vec3.hpp>

class Sphere : public Hittable
{
public:
    point3 center;
    double radius;

    Sphere() {}
    Sphere(point3 center, double radius) : center(center), radius(radius) {}

    virtual bool hit(const Ray &ray, double tmin, double tmax, Hit &hit) const;
};
