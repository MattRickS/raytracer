#include <iostream>
#include <color.hpp>
#include <ray.hpp>
#include <vec3.hpp>

bool hitSphere(const point3 &center, double radius, const Ray &ray)
{
    vec3 oc = ray.origin - center;
    double a = dot(ray.dir, ray.dir);
    double b = 2.0 * dot(oc, ray.dir);
    double c = dot(oc, oc) - radius * radius;
    double discriminant = b * b - 4 * a * c;
    return (discriminant > 0);
}

color3 rayColor(const Ray &ray)
{
    if (hitSphere(point3(0, 0, -1), 0.5, ray))
    {
        return color3(1.0, 0.0, 0.0);
    }
    vec3 dir = normalise(ray.dir);
    double delta = (dir.y + 1.0) * 0.5;
    return (1.0 - delta) * color3(1.0) + delta * color3(0.5, 0.7, 1.0);
}

int main()
{
    const double aspect = 16.0 / 9.0;
    const int width = 384;
    const int height = static_cast<int>(width / aspect);

    std::cout << "P3\n"
              << width << ' ' << height << " 255" << std::endl;

    double viewport_height = 2.0;
    double viewport_width = aspect * viewport_height;
    double focal = 1.0;

    point3 origin{0};
    vec3 horizontal{viewport_width, 0, 0};
    vec3 vertical{0, viewport_height, 0};
    vec3 lower_left = origin - horizontal / 2 - vertical / 2 - vec3(0, 0, focal);

    for (int y = height - 1; y >= 0; --y)
    {
        // std::cerr << "\rScanlines remaining: " << y << '\n'
        //           << std::flush;
        for (int x = 0; x < width; x++)
        {
            double u = double(x) / (width - 1);
            double v = double(y) / (height - 1);
            Ray ray(origin, lower_left + u * horizontal + v * vertical - origin);
            color3 pixel = rayColor(ray);
            writeColor(std::cout, pixel);
        }
    }

    std::cerr << "\nDone!\n";
    return 0;
}