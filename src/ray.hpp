#pragma once

#include <vec3.hpp>

class Ray
{
public:
    point3 origin;
    vec3 dir;
    double time;

    Ray() {}
    Ray(const point3 &origin, const vec3 &direction, double time = 0.0)
        : origin(origin), dir(direction), time(time) {}

    point3 at(double delta) const
    {
        return origin + delta * dir;
    }
};
