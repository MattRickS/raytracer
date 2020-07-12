#include <vec3.hpp>

vec3 randomUnitSphere()
{
    while (true)
    {
        vec3 p = vec3::random(-1, 1);
        if (dot(p) >= 1)
            continue;
        return p;
    }
}
