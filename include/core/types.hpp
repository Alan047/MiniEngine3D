#pragma once
#include <vector>

struct Vec3 {
    float x, y, z;
};

struct Vec4 {
    float x, y, z, w;
};

struct Mat4 {
    float m[4][4];
};

struct Bary {
    float a, b, c;
};

struct Obj {
    std::vector<Vec3> Vertices;
    std::vector<std::vector<int>> malha;
}; 
