#include <hittables/sphere.hpp>

bool Sphere::hit(const Ray &ray, double tmin, double tmax, Hit &hit) const
{
    vec3 oc = ray.origin - center;
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
            vec3 outward_normal = (hit.pos - center) / radius;
            hit.set_face_normal(ray, outward_normal);
            hit.mat_ptr = mat_ptr;
            return true;
        }
        delta = (-half_b + root) / a;
        if (delta < tmax && delta > tmin)
        {
            hit.delta = delta;
            hit.pos = ray.at(delta);
            vec3 outward_normal = (hit.pos - center) / radius;
            hit.set_face_normal(ray, outward_normal);
            hit.mat_ptr = mat_ptr;
            return true;
        }
    }
    return false;
}
