#pragma once
#include <aabb.hpp>
#include <hittables/hittable.hpp>
#include <hittables/hittable_list.hpp>
#include <vector>

class BVHNode : public Hittable
{
public:
    std::shared_ptr<Hittable> left;
    std::shared_ptr<Hittable> right;
    AABB box;

    BVHNode() {}
    BVHNode(HittableList &list, double time0, double time1)
        : BVHNode(list.objects, 0, list.objects.size(), time0, time1) {}
    BVHNode(std::vector<std::shared_ptr<Hittable>> &objects,
            size_t start, size_t end, double time0, double time1);

    virtual bool hit(const Ray &ray, double tmin, double tmax, Hit &hit) const;
    virtual bool bbox(double t0, double t1, AABB &aabb) const;
};
