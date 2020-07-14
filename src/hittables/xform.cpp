#include <hittables/xform.hpp>

bool Translate::hit(const Ray &ray, double tmin, double tmax, Hit &hit) const
{
    Ray translated(ray.origin - offset, ray.dir, ray.time);
    if (!ptr->hit(translated, tmin, tmax, hit))
    {
        return false;
    }

    hit.pos += offset;
    hit.set_face_normal(translated, hit.normal);
    return true;
}

bool Translate::bbox(double t0, double t1, AABB &aabb) const
{
    if (!ptr->bbox(t0, t1, aabb))
    {
        return false;
    }

    aabb = AABB(aabb.min() + offset, aabb.max() + offset);
    return true;
}

RotateY::RotateY(std::shared_ptr<Hittable> obj, double angle) : ptr(obj)
{
    double radians = deg2rad(angle);
    cos_theta = cos(radians);
    sin_theta = sin(radians);
    hasbox = ptr->bbox(0, 1, bounds);

    point3 min_(infinity);
    point3 max_(-infinity);

    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                double x = i * bounds.max().x + (1 - i) * bounds.min().x;
                double y = j * bounds.max().y + (1 - j) * bounds.min().y;
                double z = k * bounds.max().z + (1 - k) * bounds.min().z;

                double newx = cos_theta * x + sin_theta * z;
                double newz = -sin_theta * x + cos_theta * z;

                vec3 vec(newx, y, newz);

                for (int c = 0; c < 3; c++)
                {
                    min_[c] = fmin(min_[c], vec[c]);
                    max_[c] = fmax(max_[c], vec[c]);
                }
            }
        }
    }

    bounds = AABB(min_, max_);
}

bool RotateY::hit(const Ray &ray, double tmin, double tmax, Hit &hit) const
{
    point3 origin = ray.origin;
    vec3 dir = ray.dir;

    origin[0] = cos_theta * ray.origin[0] - sin_theta * ray.origin[2];
    origin[2] = sin_theta * ray.origin[0] + cos_theta * ray.origin[2];

    dir[0] = cos_theta * ray.dir[0] - sin_theta * ray.dir[2];
    dir[2] = sin_theta * ray.dir[0] + cos_theta * ray.dir[2];

    Ray rotated_ray(origin, dir, ray.time);
    if (!ptr->hit(rotated_ray, tmin, tmax, hit))
    {
        return false;
    }

    point3 p = hit.pos;
    vec3 n = hit.normal;

    p[0] = cos_theta * hit.pos[0] + sin_theta * hit.pos[2];
    p[2] = -sin_theta * hit.pos[0] + cos_theta * hit.pos[2];

    n[0] = cos_theta * hit.normal[0] + sin_theta * hit.normal[2];
    n[2] = -sin_theta * hit.normal[0] + cos_theta * hit.normal[2];

    hit.pos = p;
    hit.set_face_normal(rotated_ray, n);

    return true;
}
