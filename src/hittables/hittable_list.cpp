#include <hittables/hittable_list.hpp>

bool HittableList::hit(const Ray &ray, double tmin, double tmax, Hit &hit) const
{
    Hit tempHit;
    bool hitAnything = false;
    double closest = tmax;

    for (const auto &object : objects)
    {
        if (object->hit(ray, tmin, closest, tempHit))
        {
            hitAnything = true;
            closest = tempHit.delta;
            hit = tempHit;
        }
    }

    return hitAnything;
}

bool HittableList::bbox(double t0, double t1, AABB &aabb) const
{
    if (objects.empty())
    {
        return false;
    }

    AABB temp_box;
    bool first_box = true;

    for (const auto &object : objects)
    {
        if (!object->bbox(t0, t1, temp_box))
        {
            return false;
        }
        aabb = first_box ? temp_box : surroundingBox(aabb, temp_box);
        first_box = false;
    }

    return true;
}