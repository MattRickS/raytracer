#pragma once
#include <iostream>
#include <vec3.hpp>

void writeColor(std::ostream &out, color3 col)
{
    out << static_cast<int>(255.999 * col.x) << ' '
        << static_cast<int>(255.999 * col.y) << ' '
        << static_cast<int>(255.999 * col.z) << '\n';
}
