#include <hittables/box.hpp>
#include <hittables/rect.hpp>

Box::Box(const point3 &p0, const point3 &p1, std::shared_ptr<Material> material)
{
    bbox_min = p0;
    bbox_max = p1;

    sides.add(std::make_shared<XYRect>(p0.x, p1.x, p0.y, p1.y, p1.z, material));
    sides.add(std::make_shared<XYRect>(p0.x, p1.x, p0.y, p1.y, p0.z, material));
    sides.add(std::make_shared<XZRect>(p0.x, p1.x, p0.z, p1.z, p1.y, material));
    sides.add(std::make_shared<XZRect>(p0.x, p1.x, p0.z, p1.z, p0.y, material));
    sides.add(std::make_shared<YZRect>(p0.y, p1.y, p0.z, p1.z, p1.x, material));
    sides.add(std::make_shared<YZRect>(p0.y, p1.y, p0.z, p1.z, p0.x, material));
}

bool Box::hit(const Ray &ray, double tmin, double tmax, Hit &hit) const
{
    return sides.hit(ray, tmin, tmax, hit);
}
