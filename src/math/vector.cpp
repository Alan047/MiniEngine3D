#include "math/vector.hpp"
#include "core/config.hpp"
#include <cmath>

// Calcula a distância entre doi vetores

Vec3 operator-(const Vec3& a, const Vec3& b) {
    return {a.x - b.x, a.y - b.y, a.z - b.z};
}

// Resulta em um novo votor com ângulo de 90º ao plano de dois vetoers

Vec3 cross(const Vec3& a, const Vec3& b) {
    return {
        a.y*b.z - a.z*b.y,
        a.z*b.x - a.x*b.z,
        a.x*b.y - a.y*b.x
    };
}

// Operação entre dois vetores que resulta em um único número(um escalar), indicano o quanto
// o quanto eles apontam na mesma direção.

float dot(const Vec3& a, const Vec3& b) {
    return a.x*b.x + a.y*b.y + a.z*b.z;
}

// Faz com que o módulo do vetor(comprimento) seja igual a 1.

Vec3 normalize(const Vec3& v) {
    float len = std::sqrt(dot(v,v));
    return {v.x/len, v.y/len, v.z/len};
}

int toScreenX(float ndcX) {
    return (int)((ndcX + 1.0f) * 0.5f * WIDTH);
};

int toScreenY(float ndcY) {
    return (int)((1.0f - (ndcY + 1.0f) * 0.5f) * HEIGHT);
};
