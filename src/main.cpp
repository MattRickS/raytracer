#include <iostream>
#include <camera.hpp>
#include <color.hpp>
#include <hittables/hittable_list.hpp>
#include <hittables/sphere.hpp>
#include <ray.hpp>
#include <utils.hpp>
#include <vec3.hpp>

color3 rayColor(const Ray &ray, const Hittable &world)
{
    Hit hit;
    if (world.hit(ray, 0, infinity, hit))
    {
        return 0.5 * (hit.normal + color3(1.0));
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

    std::cout << "P3\n"
              << width << ' ' << height << " 255" << std::endl;

    HittableList world;
    world.add(std::make_shared<Sphere>(point3(0, 0, -1), 0.5));
    world.add(std::make_shared<Sphere>(point3(0, -100.5, -1), 100));

    Camera cam;

    for (int y = height - 1; y >= 0; --y)
    {
        // std::cerr << "\rScanlines remaining: " << y << '\n'
        //           << std::flush;
        for (int x = 0; x < width; x++)
        {
            color3 pixel{0.0};
            for (int s = 0; s < samples; ++s)
            {
                double u = (x + randDouble()) / (width - 1);
                double v = (y + randDouble()) / (height - 1);
                Ray ray = cam.projectRay(u, v);
                pixel += rayColor(ray, world);
            }
            writeColor(std::cout, pixel, samples);
        }
    }

    std::cerr << "\nDone!\n";
    return 0;
}