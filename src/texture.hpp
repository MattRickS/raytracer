#pragma once
#include <vec3.hpp>

class Texture
{
public:
    virtual color3 value(double u, double v, const point3 &pos) const = 0;
};

class SolidColor : public Texture
{
public:
    color3 color;

    SolidColor() {}
    SolidColor(color3 col) : color(col) {}
    SolidColor(double red, double green, double blue) : SolidColor(color3(red, green, blue)) {}

    virtual color3 value(double u, double v, const point3 &pos) const
    {
        return color;
    }
};
