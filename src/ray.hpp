#pragma once

#include <vec3.hpp>

class Ray
{
public:
    point3 origin;
    vec3 dir;

    Ray() {}
    Ray(const point3 &origin, const vec3 &direction) : origin(origin), dir(direction) {}

    point3 at(double delta) const
    {
        return origin + delta * dir;
    }
};
