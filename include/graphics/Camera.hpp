#pragma once
#include "math/Mat4.hpp"
#include "math/Vec3.hpp"

class Camera
{
public:
    Camera(float width, float height);

    Mat4 getViewMatrix() const;
    Mat4 getProjectionMatrix() const;

    void setPosition(const Vec3& pos);
    void setTarget(const Vec3& t);

private:
    Vec3 position;

    float fov;
    float aspect;
    float nearPlane;
    float farPlane;
    Vec3 target;
};