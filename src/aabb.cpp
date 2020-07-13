#include <aabb.hpp>

AABB surroundingBox(AABB box0, AABB box1)
{
    point3 small(fmin(box0.min().x, box1.min().x),
                 fmin(box0.min().y, box1.min().y),
                 fmin(box0.min().z, box1.min().z));
    point3 big(fmin(box0.max().x, box1.max().x),
               fmin(box0.max().y, box1.max().y),
               fmin(box0.max().z, box1.max().z));
    return AABB(small, big);
}
