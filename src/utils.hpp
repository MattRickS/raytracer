#pragma once

#include <cmath>
#include <cstdlib>
#include <limits>
#include <memory>

// Constants
const double infinity = std::numeric_limits<double>::infinity();
const double pi = 3.1415926535897932385;

// Utilities
inline double deg2rad(double degrees)
{
    return degrees * pi / 180;
}
