#include "scene/Transform.hpp"

Transform::Transform()
{
    position = {0,0,0};
    rotation = {0,0,0};
    scale    = {1,1,1};
}

Mat4 Transform::getModelMatrix() const
{
    Mat4 t = Mat4::translation(position.x,
                               position.y,
                               position.z);

    Mat4 r = Mat4::rotationY(rotation.y);

    // por enquanto ignoramos escala e outras rotações
    return t * r;
}