#include <algorithm>
#include <hittables/bvh_node.hpp>

inline bool box_compare(
    const std::shared_ptr<Hittable> lhs, const std::shared_ptr<Hittable> rhs, int axis)
{
    AABB box_a;
    AABB box_b;
    if (!lhs->bbox(0, 0, box_a) || !rhs->bbox(0, 0, box_b))
    {
        std::cerr << "No bounding box in BVHNode constructor.\n";
    }

    return box_a.min().data[axis] < box_b.min().data[axis];
}

bool box_x_compare(const std::shared_ptr<Hittable> lhs, const std::shared_ptr<Hittable> rhs)
{
    return box_compare(lhs, rhs, 0);
}

bool box_y_compare(const std::shared_ptr<Hittable> lhs, const std::shared_ptr<Hittable> rhs)
{
    return box_compare(lhs, rhs, 1);
}

bool box_z_compare(const std::shared_ptr<Hittable> lhs, const std::shared_ptr<Hittable> rhs)
{
    return box_compare(lhs, rhs, 2);
}

BVHNode::BVHNode(std::vector<std::shared_ptr<Hittable>> &objects,
                 size_t start, size_t end, double time0, double time1)
{
    int axis = 0; // randInt(0, 2);
    auto comparator = (axis == 0) ? box_x_compare
                                  : (axis == 1) ? box_y_compare
                                                : box_z_compare;

    size_t object_span = end - start;
    if (object_span == 1)
    {
        left = right = objects[start];
    }
    else if (object_span == 2)
    {
        if (comparator(objects[start], objects[start + 1]))
        {
            left = objects[start];
            right = objects[start + 1];
        }
        else
        {
            left = objects[start + 1];
            right = objects[start];
        }
    }
    else
    {
        std::sort(objects.begin() + start, objects.begin() + end, comparator);
        size_t mid = start + object_span / 2;
        left = std::make_shared<BVHNode>(objects, start, mid, time0, time1);
        right = std::make_shared<BVHNode>(objects, mid, end, time0, time1);
    }

    AABB box_left, box_right;
    if (!left->bbox(time0, time1, box_left) || !right->bbox(time0, time1, box_right))
    {
        std::cerr << "No bounding box in BVHNode constructor.\n";
    }

    box = surroundingBox(box_left, box_right);
}

bool BVHNode::bbox(double t0, double t1, AABB &aabb) const
{
    aabb = box;
    return true;
}

bool BVHNode::hit(const Ray &ray, double tmin, double tmax, Hit &hit) const
{
    if (!box.hit(ray, tmin, tmax))
    {
        return false;
    }
    bool hit_left = left->hit(ray, tmin, tmax, hit);
    bool hit_right = right->hit(ray, tmin, hit_left ? hit.delta : tmax, hit);
    return hit_left || hit_right;
}
