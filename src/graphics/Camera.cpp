#include "graphics/Camera.hpp"

Camera::Camera(float width, float height)
{
    position = {0, 0, 5};
    target = {0, 0, 0};

    fov = 90.0f * 3.14159f / 180.0f;
    aspect = width / height;
    nearPlane = 0.1f;
    farPlane = 100.0f;
}

void Camera::setPosition(const Vec3& pos)
{
    position = pos;
}

Mat4 Camera::getViewMatrix() const
{   
    // retorna a matriz VIEW como tudo da camera.
    return Mat4::lookAt(
        position,
        target,
        {0, 1, 0}
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