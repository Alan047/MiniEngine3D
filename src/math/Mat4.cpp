#include "math/Mat4.hpp"
#include <cmath>
#include <iostream>

Mat4 Mat4::identity()
{
    Mat4 result = {};

    for (int i = 0; i < 4; i++)
        result.m[i][i] = 1.0f;

    return result;
}

Mat4 Mat4::translation(float x, float y, float z)
{
    Mat4 result = identity();

    result.m[0][3] = x;
    result.m[1][3] = y;
    result.m[2][3] = z;

    return result;
}

Mat4 Mat4::rotationY(float angle)
{
    Mat4 result = identity();

    float c = cos(angle);
    float s = sin(angle);

    result.m[0][0] =  c;
    result.m[0][2] =  s;
    result.m[2][0] = -s;
    result.m[2][2] =  c;

    return result;
}

Mat4 Mat4::scale(float sx, float sy, float sz)
{
    Mat4 result = identity();

    result.m[0][0] = sx;
    result.m[1][1] = sy;
    result.m[2][2] = sz;

    return result;
}

Vec4 Mat4::operator*(const Vec4& v) const
{
    Vec4 result;

    result.x =
        m[0][0] * v.x +
        m[0][1] * v.y +
        m[0][2] * v.z +
        m[0][3] * v.w;

    result.y =
        m[1][0] * v.x +
        m[1][1] * v.y +
        m[1][2] * v.z +
        m[1][3] * v.w;

    result.z =
        m[2][0] * v.x +
        m[2][1] * v.y +
        m[2][2] * v.z +
        m[2][3] * v.w;

    result.w =
        m[3][0] * v.x +
        m[3][1] * v.y +
        m[3][2] * v.z +
        m[3][3] * v.w;

    return result;
}

Mat4 Mat4::operator*(const Mat4& other) const
{
    Mat4 result = {};

    for (int row = 0; row < 4; row++)
    {
        for (int col = 0; col < 4; col++)
        {
            result.m[row][col] =
                m[row][0] * other.m[0][col] +
                m[row][1] * other.m[1][col] +
                m[row][2] * other.m[2][col] +
                m[row][3] * other.m[3][col];
        }
    }

    return result;
}

Mat4 Mat4::perspective(float fov,
                       float aspect,
                       float near,
                       float far)
{
    Mat4 result = {};

    float f = 1.0f / tan(fov * 0.5f);

    result.m[0][0] = f / aspect;
    result.m[1][1] = f;
    result.m[2][2] = (far + near) / (near - far);
    result.m[2][3] = (2 * far * near) / (near - far);
    result.m[3][2] = 1.0f; //  reverder para negativo 

    return result;
}

Mat4 Mat4::lookAt(const Vec3& eye,
                  const Vec3& target,
                  const Vec3& up)
{
    Vec3 forward = (target - eye).normalize();
    Vec3 right = Vec3::cross(forward, up).normalize();
    Vec3 cameraUp = Vec3::cross(right, forward);

    Mat4 result = identity();

    result.m[0][0] = right.x;
    result.m[0][1] = right.y;
    result.m[0][2] = right.z;

    result.m[1][0] = cameraUp.x;
    result.m[1][1] = cameraUp.y;
    result.m[1][2] = cameraUp.z;

    result.m[2][0] = forward.x;
    result.m[2][1] = forward.y;
    result.m[2][2] = forward.z;

    result.m[0][3] = -Vec3::dot(right, eye);
    result.m[1][3] = -Vec3::dot(cameraUp, eye);
    result.m[2][3] = -Vec3::dot(forward, eye);

    return result;
}