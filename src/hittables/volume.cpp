#include <hittables/volume.hpp>

bool ConstantMedium::hit(const Ray &ray, double tmin, double tmax, Hit &hit) const
{
    const bool enableDebug = false;
    const bool debugging = enableDebug && randDouble() < 0.00001;

    Hit rec1, rec2;
    if (!boundary->hit(ray, -infinity, infinity, rec1))
    {
        return false;
    }
    if (!boundary->hit(ray, rec1.delta + 0.0001, infinity, rec2))
    {
        return false;
    }
    if (debugging)
    {
        std::cerr << "\nt0=" << rec1.delta << ", t1=" << rec2.delta << '\n';
    }

    if (rec1.delta < tmin)
    {
        rec1.delta = tmin;
    }
    if (rec2.delta > tmax)
    {
        rec2.delta = tmax;
    }

    if (rec1.delta >= rec2.delta)
    {
        return false;
    }
    if (rec1.delta < 0)
    {
        rec1.delta = 0;
    }

    const double ray_length = length(ray.dir);
    const double distance_inside_boundary = (rec2.delta - rec1.delta) * ray_length;
    const double hit_distance = neg_inv_density * log(randDouble());

    if (hit_distance > distance_inside_boundary)
    {
        return false;
    }

    hit.delta = rec1.delta + hit_distance / ray_length;
    hit.pos = ray.at(hit.delta);

    if (debugging)
    {
        std::cerr << "hit_distance = " << hit_distance << '\n'
                  << "hit.delta = " << hit.delta << '\n'
                  << "hit.pos = " << hit.pos << '\n';
    }

    hit.normal = vec3(1, 0, 0); //arbitrary
    hit.front_face = true;      // arbitrary
    hit.mat_ptr = phase_function;

    return true;
}