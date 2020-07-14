#pragma once
#include <hittables/hittable.hpp>
#include <materials/material.hpp>
#include <aabb.hpp>
#include <vec3.hpp>

class XYRect : public Hittable
{
public:
    double x0, x1, y0, y1, k;
    std::shared_ptr<Material> mat_ptr;

    XYRect() {}
    XYRect(double x0, double x1, double y0, double y1, double k, std::shared_ptr<Material> material)
        : x0(x0), x1(x1), y0(y0), y1(y1), k(k), mat_ptr(material) {}

    virtual bool hit(const Ray &ray, double tmin, double tmax, Hit &hit) const;
    virtual bool bbox(double t0, double t1, AABB &aabb) const
    {
        // Pad Z dimension to have a finite thickness
        aabb = AABB(point3(x0, y0, k - 0.00001), point3(x1, y1, k + 0.00001));
        return true;
    }
};

class XZRect : public Hittable
{
public:
    double x0, x1, z0, z1, k;
    std::shared_ptr<Material> mat_ptr;

    XZRect() {}
    XZRect(double x0, double x1, double z0, double z1, double k, std::shared_ptr<Material> material)
        : x0(x0), x1(x1), z0(z0), z1(z1), k(k), mat_ptr(material) {}

    virtual bool hit(const Ray &ray, double tmin, double tmax, Hit &hit) const;
    virtual bool bbox(double t0, double t1, AABB &aabb) const
    {
        // Pad Z dimension to have a finite thickness
        aabb = AABB(point3(x0, k - 0.00001, z0), point3(x1, k + 0.00001, z1));
        return true;
    }
};

class YZRect : public Hittable
{
public:
    double y0, y1, z0, z1, k;
    std::shared_ptr<Material> mat_ptr;

    YZRect() {}
    YZRect(double y0, double y1, double z0, double z1, double k, std::shared_ptr<Material> material)
        : y0(y0), y1(y1), z0(z0), z1(z1), k(k), mat_ptr(material) {}

    virtual bool hit(const Ray &ray, double tmin, double tmax, Hit &hit) const;
    virtual bool bbox(double t0, double t1, AABB &aabb) const
    {
        // Pad Z dimension to have a finite thickness
        aabb = AABB(point3(k - 0.00001, y0, z0), point3(k + 0.00001, y1, z1));
        return true;
    }
};