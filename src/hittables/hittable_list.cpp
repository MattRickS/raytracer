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