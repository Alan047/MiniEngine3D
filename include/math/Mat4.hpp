#pragma once
#include "math/Vec4.hpp"
#include "math/Vec3.hpp"

struct Mat4
{
    float m[4][4];

    static Mat4 identity();
    static Mat4 translation(float x, float y, float z);
    static Mat4 rotationY(float angle);
    static Mat4 perspective(float fov, float aspect, float near, float far);
    static Mat4 lookAt(const Vec3& eye, const Vec3& target, const Vec3& up);

    Vec4 operator*(const Vec4& v) const;
    Mat4 operator*(const Mat4& other) const;
};

