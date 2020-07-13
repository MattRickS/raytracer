#include <vec3.hpp>

vec3 randomUnitDisk()
{
    while (true)
    {
        vec3 pos = vec3(randDouble(-1, 1), randDouble(-1, 1), 0);
        if (dot(pos) >= 1)
            continue;
        return pos;
    }
}

vec3 randomUnitSphere()
{
    while (true)
    {
        vec3 p = vec3::random(-1, 1);
        if (dot(p) >= 1)
            continue;
        return p;
    }
}

vec3 randomUnitVector()
{
    double a = randDouble(0, 2 * pi);
    double z = randDouble(-1, 1);
    double r = std::sqrt(1 - z * z);
    return vec3(r * cos(a), r * sin(a), z);
}

vec3 randomUnitHemisphere(const vec3 &normal)
{
    vec3 unit_sphere = randomUnitSphere();
    if (dot(unit_sphere, normal) > 0.0)
    {
        return unit_sphere;
    }
    else
    {
        return -unit_sphere;
    }
}

vec3 reflect(const vec3 &v, const vec3 &normal)
{
    return v - 2 * dot(v, normal) * normal;
}

vec3 refract(const vec3 &v, const vec3 &normal, double etai_over_etat)
{
    double cos_theta = dot(-v, normal);
    vec3 r_parallel = etai_over_etat * (v + cos_theta * normal);
    vec3 r_perpendicular = -sqrt(1.0 - dot(r_parallel)) * normal;
    return r_parallel + r_perpendicular;
}
