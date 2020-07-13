#pragma once
#include <aabb.hpp>
#include <hittables/hittable.hpp>
#include <materials/material.hpp>

class MovingSphere : public Hittable
{
public:
    point3 center0;
    point3 center1;
    double time0;
    double time1;
    double radius;
    std::shared_ptr<Material> mat_ptr;

    MovingSphere() {}
    MovingSphere(point3 center0, point3 center1, double t0, double t1, double r, std::shared_ptr<Material> material)
        : center0(center0), center1(center1), time0(t0), time1(t1), radius(r), mat_ptr(material) {}

    virtual bool hit(const Ray &ray, double tmin, double tmax, Hit &hit) const;
    virtual bool bbox(double t0, double t1, AABB &aabb) const;

    point3 center(double time) const;
};