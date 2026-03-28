#include "graphics/Camera.hpp"

Camera::Camera(float width, float height)
{
    position = {0, 5, -5};
    target = {0, 0, 0};
    up = {0, 1, 0};
    

    fov = 90.0f * 3.14159f / 180.0f;
    aspect = width / height;
    nearPlane = 0.1f;
    farPlane = 100.0f;
}


Mat4 Camera::getViewMatrix() const
{   
    // retorna a matriz VIEW como tudo da camera.
    return Mat4::lookAt(
        position,
        target,
        up
    );
}

Mat4 Camera::getProjectionMatrix() const
{
    return Mat4::perspective(
        fov,
        aspect,
        nearPlane,
        farPlane
    );
}

void Camera::setPosition(const Vec3& pos)
{
    position = pos;
}

bool Camera::isBackFacing(const Vec3& a, const Vec3& b, const Vec3& c)
{
    Vec3 ab = b - a;
    Vec3 ac = c - a;

    Vec3 normal = Vec3::cross(ab, ac);

    float d = Vec3::dot(normal, position);

    return d >= 0.0f;
}