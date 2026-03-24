#pragma once
#include "math/Vec3.hpp"
#include "math/Mat4.hpp"

class Transform {
public:
    Vec3 position;
    Vec3 rotation;
    Vec3 scale;

    Transform();

    Mat4 getModelMatrix() const;
};