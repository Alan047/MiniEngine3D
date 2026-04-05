#pragma once
#include "math/Mat4.hpp"
#include "math/Vec3.hpp"
#include <cstdint>
#include <SDL2/SDL.h>

class Camera
{
public:
    Camera(float width, float height);

    Mat4 getViewMatrix() const;
    Mat4 getProjectionMatrix() const;

    void setPosition(const Vec3& pos);
    void setTarget(const Vec3& t);
    bool isBackFacing(const Vec3& a, const Vec3& b, const Vec3& c);
    void update(float deltaTime, const uint8_t* keyboardState);
    void processMouseMovement(int dx, int dy);
    Vec3 getPositionCamera();

private:
    Vec3 position;

    float fov;
    float aspect;
    float nearPlane;
    float farPlane;
    Vec3 target;
    Vec3 up;
    float yaw;
    float pitch;

    float sensitivity;
};