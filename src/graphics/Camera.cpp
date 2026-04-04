#include "graphics/Camera.hpp"
#include <cmath>
#include <iostream>

Camera::Camera(float width, float height)
{
    position = {0, 0, 5};
    target = {0, 0, 0};
    up = {0, 1, 0};
    

    fov = 90.0f * 3.14159f / 180.0f;
    aspect = width / height;
    nearPlane = 0.1f;
    farPlane = 100.0f;

    yaw = -90.0f;
    pitch = 0.0f;

    sensitivity = 0.1f;

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

void Camera::update(float deltaTime, const uint8_t* keyboardState)
{
    float speed = 3.0f * deltaTime;

    Vec3 forward = (target - position).normalize();
    Vec3 right = Vec3::cross(forward, {0,1,0}).normalize();

    if (keyboardState[SDL_SCANCODE_W])
    {
        position = position + forward * speed;
        target = target + forward * speed;
    }

    if (keyboardState[SDL_SCANCODE_S])
    {
        position = position - forward * speed;
        target   = target   - forward * speed;
    }

    // Esquerda / direita
    if (keyboardState[SDL_SCANCODE_A])
    {
        position = position - right * speed;
        target   = target   - right * speed;
    }

    if (keyboardState[SDL_SCANCODE_D])
    {
        position = position + right * speed;
        target   = target   + right * speed;
    }
    
}

void Camera::processMouseMovement(int dx, int dy)
{
    std::cout << "dx: " << dx << " dy: " << dy << "\n";

    yaw += dx * sensitivity;
    pitch -= dy * sensitivity;

    if (pitch > 89.0f) pitch = 89.0f;
    if (pitch < -89.0f) pitch = -89.0f;

    float yawRad = yaw * 3.14159f / 180.0f;
    float pitchRad = pitch * 3.14159f / 180.0f;

    Vec3 direction;

    direction.x = cos(pitchRad) * cos(yawRad);
    direction.y = sin(pitchRad);
    direction.z = cos(pitchRad) * sin(yawRad);

    direction = direction.normalize();

    target = position + direction;
}