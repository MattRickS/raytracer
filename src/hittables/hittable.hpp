#pragma once
#include <aabb.hpp>
#include <ray.hpp>
#include <vec3.hpp>

class Material;

struct Hit
{
    point3 pos;
    vec3 normal;
    std::shared_ptr<Material> mat_ptr;
    double delta;
    double u;
    double v;
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
    virtual bool bbox(double t0, double t1, AABB &aabb) const = 0;
};