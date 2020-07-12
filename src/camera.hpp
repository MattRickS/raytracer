#pragma once
#include <ray.hpp>
#include <vec3.hpp>

class Camera
{
public:
    Camera()
    {
        double aspect = 16.0 / 9.0;
        double viewport_height = 2.0;
        double viewport_width = aspect * viewport_height;
        double focal = 1.0;

        origin = point3{0};
        horizontal = vec3{viewport_width, 0, 0};
        vertical = vec3{0, viewport_height, 0};
        lower_left = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal);
    }

    Ray projectRay(double u, double v) const
    {
        return Ray(origin, lower_left + u * horizontal + v * vertical - origin);
    }

private:
    point3 origin;
    point3 lower_left;
    vec3 horizontal;
    vec3 vertical;
};