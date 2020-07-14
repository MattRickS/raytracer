#pragma once
#include <hittables/hittable.hpp>

class Translate : public Hittable
{
public:
    std::shared_ptr<Hittable> ptr;
    vec3 offset;

    Translate(std::shared_ptr<Hittable> obj, const vec3 &displacement)
        : ptr(obj), offset(displacement) {}

    virtual bool hit(const Ray &ray, double tmin, double tmax, Hit &hit) const;
    virtual bool bbox(double t0, double t1, AABB &aabb) const;
};

class RotateY : public Hittable
{
public:
    std::shared_ptr<Hittable> ptr;
    double cos_theta;
    double sin_theta;
    bool hasbox;
    AABB bounds;

    RotateY(std::shared_ptr<Hittable> obj, double angle);

    virtual bool hit(const Ray &ray, double tmin, double tmax, Hit &hit) const;
    virtual bool bbox(double t0, double t1, AABB &aabb) const
    {
        aabb = bounds;
        return true;
    }
};
