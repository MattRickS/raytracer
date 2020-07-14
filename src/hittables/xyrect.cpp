#include <hittables/xyrect.hpp>

bool XYRect::hit(const Ray &ray, double tmin, double tmax, Hit &hit) const
{
    double t = (k - ray.origin.z) / ray.dir.z;
    if (t < tmin || t > tmax)
    {
        return false;
    }

    double x = ray.origin.x + t * ray.dir.x;
    double y = ray.origin.y + t * ray.dir.y;
    if (x < x0 || x > x1 || y < y0 || y > y1)
    {
        return false;
    }

    hit.u = (x - x0) / (x1 - x0);
    hit.v = (y - y0) / (y1 - y0);
    hit.delta = t;
    hit.mat_ptr = mat_ptr;
    vec3 normal = vec3(0, 1, 0);
    hit.set_face_normal(ray, normal);
    hit.pos = ray.at(t);
    return true;
}
