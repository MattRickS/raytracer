#pragma once
#include <ray.hpp>
#include <vec3.hpp>

class Camera
{
public:
    Camera(
        point3 pos,
        point3 lookat,
        vec3 up,
        double fov, // horizontal field of view in degrees
        double aspect)
    {
        double theta = deg2rad(fov);
        double h = tan(theta / 2.0);
        double viewport_width = 2.0 * h;
        double viewport_height = viewport_width / aspect;

        vec3 forward = normalise(pos - lookat);
        vec3 right = normalise(cross(up, forward));
        vec3 up_vec = cross(forward, right);

        origin = pos;
        horizontal = viewport_width * right;
        vertical = viewport_height * up_vec;
        lower_left = origin - horizontal / 2 - vertical / 2 - forward;
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