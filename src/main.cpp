#include <iostream>
#include <camera.hpp>
#include <color.hpp>
#include <hittables/hittable_list.hpp>
#include <hittables/sphere.hpp>
#include <ray.hpp>
#include <utils.hpp>
#include <vec3.hpp>

color3 rayColor(const Ray &ray, const Hittable &world, int depth)
{
    if (depth <= 0)
    {
        return color3(0);
    }

    Hit hit;
    if (world.hit(ray, 0.001, infinity, hit))
    {
        point3 target = hit.pos + randomHemisphere(hit.normal);
        return 0.5 * rayColor(Ray(hit.pos, target - hit.pos), world, depth - 1);
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
    const int samples = 100;
    const int max_depth = 50;

    std::cout << "P3\n"
              << width << ' ' << height << " 255" << std::endl;

    HittableList world;
    world.add(std::make_shared<Sphere>(point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(point3(0, -100.5, -1), 100));

    Camera cam;

    for (int y = height - 1; y >= 0; --y)
    {
        std::cerr << "\rScanlines remaining: " << y << '\n'
                  << std::flush;
        for (int x = 0; x < width; x++)
        {
            color3 pixel{0.0};
            for (int s = 0; s < samples; ++s)
            {
                double u = (x + randDouble()) / (width - 1);
                double v = (y + randDouble()) / (height - 1);
                Ray ray = cam.projectRay(u, v);
                pixel += rayColor(ray, world, max_depth);
            }
            writeColor(std::cout, pixel, samples);
        }
    }

    std::cerr << "\nDone!\n";
    return 0;
}