#pragma once
#include "core/types.hpp"

Mat4 identidade();
Mat4 translacao(float x, float y, float z);
Mat4 rotacaoY(float rad);
Mat4 look(const Vec3& pos, const Vec3& target, const Vec3& up);
Mat4 perspectiva(float fov, float aspect, float near, float far);

Mat4 operator*(const Mat4& a, const Mat4& b);
Vec4 transform4(const Mat4& m, const Vec3& v);
