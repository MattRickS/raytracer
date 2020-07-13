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
        double aspect,
        double aperture,
        double focus_dist)
    {
        double theta = deg2rad(fov);
        double h = tan(theta / 2.0);
        double viewport_width = 2.0 * h;
        double viewport_height = viewport_width / aspect;

        forward = normalise(pos - lookat);
        right = normalise(cross(up, forward));
        up_vec = cross(forward, right);

        origin = pos;
        horizontal = focus_dist * viewport_width * right;
        vertical = focus_dist * viewport_height * up_vec;
        lower_left = origin - horizontal / 2 - vertical / 2 - focus_dist * forward;

        lens_radius = aperture / 2;
    }

    Ray projectRay(double u, double v) const
    {
        vec3 lens_offset = lens_radius * randomUnitDisk();
        vec3 offset = right * lens_offset.x + up_vec * lens_offset.y;
        return Ray(
            origin + offset,
            lower_left + u * horizontal + v * vertical - origin - offset);
    }

private:
    point3 origin;
    point3 lower_left;
    vec3 horizontal;
    vec3 vertical;
    vec3 forward, right, up_vec;
    double lens_radius;
};