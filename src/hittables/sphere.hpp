#pragma once
#include <hittables/hittable.hpp>
#include <materials/material.hpp>
#include <aabb.hpp>
#include <vec3.hpp>

class Sphere : public Hittable
{
public:
    point3 center;
    double radius;
    std::shared_ptr<Material> mat_ptr;

    Sphere() {}
    Sphere(point3 center, double radius, std::shared_ptr<Material> material)
        : center(center), radius(radius), mat_ptr(material) {}

    virtual bool hit(const Ray &ray, double tmin, double tmax, Hit &hit) const;
    virtual bool bbox(double t0, double t1, AABB &aabb) const;
};

void sphereUV(const point3 &center, double &u, double &v);
