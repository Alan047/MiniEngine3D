#include "math/matrix.hpp"
#include "math/vector.hpp"
#include <cmath>

Mat4 identidade() {
    Mat4 r = {};
    
    r.m[0][0] = 1;
    r.m[1][1] = 1;
    r.m[2][2] = 1;
    r.m[3][3] = 1;

    return r;
};

Mat4  operator*(const Mat4& a, const Mat4& b) {
    Mat4 r{};
    
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            r.m[j][i] = 
            a.m[0][i] * b.m[j][0] +
            a.m[1][i] * b.m[j][1] +
            a.m[2][i] * b.m[j][2] +
            a.m[3][i] * b.m[j][3];
        }
    }
    
    return r;
};

// TRANSFORMS

Vec3 transformar(const Mat4& m, const Vec3& v) {
    Vec3 r;
    
    r.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z *m.m[2][0] + m.m[3][0];
    r.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z *m.m[2][1] + m.m[3][1];
    r.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z *m.m[2][2] + m.m[3][2];
    
    return r;
};

Vec4 transform4(const Mat4& m, const Vec3& v) {
    Vec4 r;
    r.x = v.x * m.m[0][0] + v.y * m.m[1][0] + v.z * m.m[2][0] + m.m[3][0];
    r.y = v.x * m.m[0][1] + v.y * m.m[1][1] + v.z * m.m[2][1] + m.m[3][1];
    r.z = v.x * m.m[0][2] + v.y * m.m[1][2] + v.z * m.m[2][2] + m.m[3][2];
    r.w = v.x * m.m[0][3] + v.y * m.m[1][3] + v.z * m.m[2][3] + m.m[3][3];
    return r;
};

// MATRIX MODEL(TRANFORMAÇÕES)

Mat4 escala(float x, float y, float z) {
    Mat4 r = {};
    
    r.m[0][0] = x;
    r.m[1][1] = y;
    r.m[2][2] = z;
    r.m[3][3] = 1;
    
    return r;
};

Mat4 rotacaoX(float anguloRad) {
    Mat4 r = identidade();
    
    float c = cos(anguloRad);
    float s = sin(anguloRad);
    
    r.m[1][1] = c;
    r.m[2][1] = s;
    r.m[1][2] =-s;
    r.m[2][2] = c;
    
    return r;
};
Mat4 rotacaoY(float anguloRad) {
    Mat4 r = identidade();
    
    float c = cos(anguloRad);
    float s = sin(anguloRad);
    
    r.m[0][0] = c;
    r.m[2][0] = s;
    r.m[0][2] =-s;
    r.m[2][2] = c;
    
    return r;
};

Mat4 rotacaoZ(float anguloRad) {
    Mat4 r = identidade();
    
    float c = cos(anguloRad);
    float s = sin(anguloRad);
    
    r.m[0][0] = c;
    r.m[1][0] = s;
    r.m[0][1] =-s;
    r.m[1][1] = c;
    
    return r;
};

Mat4 translacao(float x, float y, float z) {
    Mat4 r = identidade();
    
    r.m[3][0] = x;
    r.m[3][1] = y;
    r.m[3][2] = z;
    
    return r;
};

// VIEW MATRIX (MATRIZES DA CAMERA)

Mat4 look(const Vec3& pos, const Vec3& target, const Vec3& up) {
    Vec3 forward = normalize(target - pos); //Direção;
    Vec3 right = normalize(cross(forward, up)); //lado;
    Vec3 upReal = cross(right, forward); //cima real;
    
    Mat4 view = identidade();
    
    view.m[0][0] = right.x;
    view.m[1][0] = right.y;
    view.m[2][0] = right.z;

    view.m[0][1] = upReal.x;
    view.m[1][1] = upReal.y;
    view.m[2][1] = upReal.z;

    view.m[0][2] = -forward.x;
    view.m[1][2] = -forward.y;
    view.m[2][2] = -forward.z;

    view.m[3][0] = -dot(right, pos);
    view.m[3][1] = -dot(upReal, pos);
    view.m[3][2] =  dot(forward, pos);
    
    return view;
};

// VIEW PROJECTIOM(MATRIZ DE PROJEÇÃO)

Mat4 perspectiva(float fovRad, float aspect, float nearZ, float farZ) {
    float f = 1.0f / tanf(fovRad / 2.0f);

    Mat4 r = {};

    r.m[0][0] = f / aspect;
    r.m[1][1] = f;
    r.m[2][2] = (farZ + nearZ) / (nearZ - farZ);
    r.m[2][3] = -1.0f;
    r.m[3][2] = (2.0f * farZ * nearZ) / (nearZ - farZ);

    return r;
}
