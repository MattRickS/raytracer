#include <hittables/rect.hpp>

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
    vec3 normal = vec3(0, 0, 1);
    hit.set_face_normal(ray, normal);
    hit.pos = ray.at(t);
    return true;
}

bool XZRect::hit(const Ray &ray, double tmin, double tmax, Hit &hit) const
{
    double t = (k - ray.origin.y) / ray.dir.y;
    if (t < tmin || t > tmax)
    {
        return false;
    }

    double x = ray.origin.x + t * ray.dir.x;
    double z = ray.origin.z + t * ray.dir.z;
    if (x < x0 || x > x1 || z < z0 || z > z1)
    {
        return false;
    }

    hit.u = (x - x0) / (x1 - x0);
    hit.v = (z - z0) / (z1 - z0);
    hit.delta = t;
    hit.mat_ptr = mat_ptr;
    vec3 normal = vec3(0, 1, 0);
    hit.set_face_normal(ray, normal);
    hit.pos = ray.at(t);
    return true;
}

bool YZRect::hit(const Ray &ray, double tmin, double tmax, Hit &hit) const
{
    double t = (k - ray.origin.x) / ray.dir.x;
    if (t < tmin || t > tmax)
    {
        return false;
    }

    double y = ray.origin.y + t * ray.dir.y;
    double z = ray.origin.z + t * ray.dir.z;
    if (y < y0 || y > y1 || z < z0 || z > z1)
    {
        return false;
    }

    hit.u = (y - y0) / (y1 - y0);
    hit.v = (z - z0) / (z1 - z0);
    hit.delta = t;
    hit.mat_ptr = mat_ptr;
    vec3 normal = vec3(1, 0, 0);
    hit.set_face_normal(ray, normal);
    hit.pos = ray.at(t);
    return true;
}
