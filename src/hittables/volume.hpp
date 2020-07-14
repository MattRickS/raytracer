#pragma once
#include <hittables/hittable.hpp>
#include <materials/isotropic.hpp>
#include <texture.hpp>

class ConstantMedium : public Hittable
{
public:
    std::shared_ptr<Hittable> boundary;
    std::shared_ptr<Material> phase_function;
    double neg_inv_density;

    ConstantMedium(std::shared_ptr<Hittable> bounds, double d, std::shared_ptr<Texture> tex)
        : boundary(bounds), neg_inv_density(-1 / d)
    {
        phase_function = std::make_shared<Isotropic>(tex);
    }

    virtual bool hit(const Ray &ray, double tmin, double tmax, Hit &hit) const;
    virtual bool bbox(double t0, double t1, AABB &aabb) const
    {
        return boundary->bbox(t0, t1, aabb);
    }
};