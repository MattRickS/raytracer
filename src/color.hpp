#pragma once
#include <iostream>
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
