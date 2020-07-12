#pragma once
#include <ray.hpp>
#include <vec3.hpp>

struct Hit
{
    point3 pos;
    vec3 normal;
    double delta;
    bool front_face;

    inline void set_face_normal(const Ray &ray, const vec3 &outward_normal)
    {
        front_face = dot(ray.dir, outward_normal) < 0;
        normal = front_face ? outward_normal : -outward_normal;
    }
};

class Hittable
{
public:
    virtual bool hit(const Ray &ray, double tmin, double tmax, Hit &hit) const = 0;
};