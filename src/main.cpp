#include <iostream>
#include <camera.hpp>
#include <hittables/hittable_list.hpp>
#include <hittables/sphere.hpp>
#include <hittables/moving_sphere.hpp>
#include <materials/dielectric.hpp>
#include <materials/lambertian.hpp>
#include <materials/material.hpp>
#include <materials/metal.hpp>
#include <ray.hpp>
#include <utils.hpp>
#include <vec3.hpp>

void writeColor(std::ostream &out, color3 col, int samples)
{
    double scale = 1.0 / samples;
    double r = std::pow(scale * col.r, 0.5);
    double g = std::pow(scale * col.g, 0.5);
    double b = std::pow(scale * col.b, 0.5);

    out << static_cast<int>(256 * clamp(r, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(g, 0.0, 0.999)) << ' '
        << static_cast<int>(256 * clamp(b, 0.0, 0.999)) << '\n';
}

color3 rayColor(const Ray &ray, const Hittable &world, int depth)
{
    if (depth <= 0)
    {
        return color3(0);
    }

    Hit hit;
    if (world.hit(ray, 0.001, infinity, hit))
    {
        Ray scattered;
        color3 attenuation;
        if (hit.mat_ptr->scatter(ray, hit, attenuation, scattered))
        {
            return attenuation * rayColor(scattered, world, depth - 1);
        }
        return color3(0);
    }
    vec3 dir = normalise(ray.dir);
    double delta = (dir.y + 1.0) * 0.5;
    return (1.0 - delta) * color3(1.0) + delta * color3(0.5, 0.7, 1.0);
}

HittableList randomScene()
{
    HittableList world;

    auto ground_material = std::make_shared<Lambertian>(color3(0.5));
    world.add(std::make_shared<Sphere>(point3(0, -1000, 0), 1000, ground_material));

    for (int a = -11; a < 11; a++)
    {
        for (int b = -11; b < 11; b++)
        {
            double material_choice = randDouble();
            point3 center(a + 0.9 * randDouble(), 0.2, b + 0.9 * randDouble());

            if (length(center - point3(4, 0.2, 0)) > 0.9)
            {
                std::shared_ptr<Material> sphere_material;

                if (material_choice < 0.8)
                {
                    // diffuse
                    color3 albedo = color3::random() * color3::random();
                    sphere_material = std::make_shared<Lambertian>(albedo);
                    point3 center2 = center + vec3(0, randDouble(0, 0.25), 0);
                    world.add(std::make_shared<MovingSphere>(
                        center, center2, 0.0, 1.0, 0.2, sphere_material));
                }
                else if (material_choice < 0.95)
                {
                    // metal
                    color3 albedo = color3::random(0.5, 1);
                    double fuzz = randDouble(0, 0.5);
                    sphere_material = std::make_shared<Metal>(albedo, fuzz);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
                else
                {
                    // glass
                    sphere_material = std::make_shared<Dielectric>(1.5);
                    world.add(std::make_shared<Sphere>(center, 0.2, sphere_material));
                }
            }
        }
    }

    auto material1 = std::make_shared<Dielectric>(1.5);
    world.add(std::make_shared<Sphere>(point3(0, 1, 0), 1.0, material1));

    auto material2 = std::make_shared<Lambertian>(color3(0.4, 0.2, 0.1));
    world.add(std::make_shared<Sphere>(point3(-4, 1, 0), 1.0, material2));

    auto material3 = std::make_shared<Metal>(color3(0.7, 0.6, 0.5), 0.0);
    world.add(std::make_shared<Sphere>(point3(4, 1, 0), 1.0, material3));

    return world;
}

int main()
{
    const double aspect = 16.0 / 9.0;
    const int width = 192;
    const int height = static_cast<int>(width / aspect);
    const int samples = 100;
    const int max_depth = 50;

    std::cout << "P3\n"
              << width << ' ' << height << " 255" << std::endl;

    HittableList world = randomScene();
    // world.add(std::make_shared<Sphere>(
    //     point3(0, 0, -1), 0.5, std::make_shared<Lambertian>(color3(0.7, 0.3, 0.3))));
    // world.add(std::make_shared<Sphere>(
    //     point3(0, -100.5, -1), 100, std::make_shared<Lambertian>(color3(0.8, 0.8, 0.0))));
    // world.add(std::make_shared<Sphere>(
    //     point3(1, 0, -1), 0.5, std::make_shared<Metal>(color3(0.8, 0.6, 0.2), 0.3)));
    // world.add(std::make_shared<Sphere>(
    //     point3(-1, 0, -1), 0.5, std::make_shared<Dielectric>(1.5)));
    // world.add(std::make_shared<Sphere>(
    //     point3(-1, 0, -1), -0.45, std::make_shared<Dielectric>(1.5)));

    // point3 cam_pos(-3, 3, 2);
    // point3 cam_target(0, 0, -1);
    // double focus_dist{length(cam_pos - cam_target)};
    // Camera cam(cam_pos, cam_target, vec3(0, 1, 0), 34.4, 1.77, 0.4, focus_dist);

    point3 cam_pos(13, 2, 3);
    point3 cam_target(0);
    double focus_dist{10.0};
    double aperture{0.1};
    Camera cam(cam_pos, cam_target, vec3(0, 1, 0), 34.4, aspect, aperture, focus_dist);

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