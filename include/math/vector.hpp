#pragma once
#include "core/types.hpp"

Vec3 operator-(const Vec3& a, const Vec3& b);
Vec3 cross(const Vec3& a, const Vec3& b);
float dot(const Vec3& a, const Vec3& b);
Vec3 normalize(const Vec3& v);
int toScreenX(float ndcX);
int toScreenY(float ndcY);
