#pragma once

struct Vec3
{
    float x, y, z;

    static float dot(const Vec3& a, const Vec3& b);
    static Vec3 cross(const Vec3& a, const Vec3& b);

    Vec3();
    Vec3(float x, float y, float z);
    float length() const;
    Vec3 normalize() const;

    Vec3 operator+(const Vec3& v) const;
    Vec3 operator-(const Vec3& v) const;
    Vec3 operator*(float scalar) const;
};