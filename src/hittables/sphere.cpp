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
            sphereUV((hit.pos - center) / radius, hit.u, hit.v);
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
            sphereUV((hit.pos - center) / radius, hit.u, hit.v);
            return true;
        }
    }
    return false;
}

bool Sphere::bbox(double t0, double t1, AABB &aabb) const
{
    aabb = AABB(center - vec3(radius), center + vec3(radius));
    return true;
}

void sphereUV(const point3 &pos, double &u, double &v)
{
    double phi = atan2(pos.z, pos.x);
    double theta = asin(pos.y);
    u = 1 - (phi + pi) / (2 * pi);
    v = (theta + pi / 2) / pi;
}
