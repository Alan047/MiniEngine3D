#include "math/Vec3.hpp"
#include <cmath>

// Construtores

Vec3::Vec3() : x(0), y(0), z(0) {}

Vec3::Vec3(float x, float y, float z)
    : x(x), y(y), z(z) {}

// Sobrecarga de operadoes

Vec3 Vec3::operator+(const Vec3& v) const
{
    return { x + v.x, y + v.y, z + v.z };
}

Vec3 Vec3::operator-(const Vec3& v) const
{
    return { x - v.x, y - v.y, z - v.z };
}

Vec3 Vec3::operator*(float scalar) const
{
    return { x * scalar, y * scalar, z * scalar };
}

// Operações com Vetores

float Vec3::length() const
{
    return std::sqrt(x*x + y*y + z*z); // retorna o tamanha do vetor(hipotenuza).
}

Vec3 Vec3::normalize() const
{
    float len = length();
    return { x/len, y/len, z/len }; // o tamanho de vetor passa ser igual 1.
}

float Vec3::dot(const Vec3& a, const Vec3& b) // angulo entre dois vetores.
{
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

Vec3 Vec3::cross(const Vec3& a, const Vec3& b) // retorna um vetor ortogonal ao plano de dois outros vetores A X B.
{
    return {
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    };
}