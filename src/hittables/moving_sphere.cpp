#include <hittables/moving_sphere.hpp>

point3 MovingSphere::center(double time) const
{
    return center0 + ((time - time0) / (time1 - time0)) * (center1 - center0);
}

bool MovingSphere::hit(const Ray &ray, double tmin, double tmax, Hit &hit) const
{
    vec3 oc = ray.origin - center(ray.time);
    double a = dot(ray.dir);
    double half_b = dot(oc, ray.dir);
    double c = dot(oc) - radius * radius;
    double discriminant = half_b * half_b - a * c;
    if (discriminant > 0)
    {
        double root = std::sqrt(discriminant);
        double delta = (-half_b - root) / a;
        if (delta < tmax && delta > tmin)
        {
            hit.delta = delta;
            hit.pos = ray.at(delta);
            vec3 outward_normal = (hit.pos - center(ray.time)) / radius;
            hit.set_face_normal(ray, outward_normal);
            hit.mat_ptr = mat_ptr;
            return true;
        }
        delta = (-half_b + root) / a;
        if (delta < tmax && delta > tmin)
        {
            hit.delta = delta;
            hit.pos = ray.at(delta);
            vec3 outward_normal = (hit.pos - center(ray.time)) / radius;
            hit.set_face_normal(ray, outward_normal);
            hit.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}

bool MovingSphere::bbox(double t0, double t1, AABB &aabb) const
{
    AABB box0(center(t0) - vec3(radius), center(t0) + vec3(radius));
    AABB box1(center(t1) - vec3(radius), center(t1) + vec3(radius));
    aabb = surroundingBox(box0, box1);
    return true;
}
