#include <vec3.hpp>

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

vec3 randomHemisphere(const vec3 &normal)
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
