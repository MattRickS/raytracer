#pragma once
#include <ray.hpp>
#include <vec3.hpp>

class AABB
{
public:
    AABB() {}
    AABB(const point3 &bmin, const point3 &bmax)
    {
        _min = bmin;
        _max = bmax;
    }

    point3 min() const { return _min; }
    point3 max() const { return _max; }

    bool hit(const Ray &ray, double tmin, double tmax) const;

private:
    point3 _min;
    point3 _max;
};

inline bool AABB::hit(const Ray &ray, double tmin, double tmax) const
{
    for (int i = 0; i < 3; i++)
    {
        double invD = 1.0f / ray.dir[i];
        double t0 = (_min[i] - ray.origin[i]) * invD;
        double t1 = (_max[i] - ray.origin[i]) * invD;
        if (invD < 0.0f)
        {
            std::swap(t0, t1);
        }
        tmin = t0 > tmin ? t0 : tmin;
        tmax = t1 > tmax ? t1 : tmax;
        if (tmax <= tmin)
        {
            return false;
        }
    }
    return true;
}

AABB surroundingBox(AABB box0, AABB box1);
