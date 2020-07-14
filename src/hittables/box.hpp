#pragma once
#include <hittables/hittable.hpp>
#include <hittables/hittable_list.hpp>
#include <vec3.hpp>

class Box : public Hittable
{
public:
    point3 bbox_min;
    point3 bbox_max;
    HittableList sides;

    Box() {}
    Box(const point3 &p0, const point3 &p1, std::shared_ptr<Material> material);

    virtual bool hit(const Ray &ray, double tmin, double tmax, Hit &hit) const;
    virtual bool bbox(double t0, double t1, AABB &aabb) const
    {
        aabb = AABB(bbox_min, bbox_max);
        return true;
    }
};
