#pragma once
#include <aabb.hpp>
#include <hittables/hittable.hpp>
#include <memory>
#include <vector>

class HittableList : public Hittable
{
public:
    std::vector<std::shared_ptr<Hittable>> objects;

    HittableList() {}
    HittableList(std::shared_ptr<Hittable> object) { add(object); }

    void clear() { objects.clear(); }
    void add(std::shared_ptr<Hittable> object) { objects.push_back(object); }

    virtual bool hit(const Ray &ray, double tmin, double tmax, Hit &hit) const;
    virtual bool bbox(double t0, double t1, AABB &aabb) const;
};
