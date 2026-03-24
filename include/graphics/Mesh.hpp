#pragma once
#include <vector>
#include "math/Vec3.hpp"
#include <string>

struct Edge {
    int a;
    int b;
};

struct Triangle {
    int a;
    int b;
    int c;
};

class Mesh {
public:
    std::vector<Vec3> vertices;
    std::vector<Triangle> triangles;

    static Mesh createCube();
    static Mesh createBox(float w,
                      float h,
                      float d);
    
    static Mesh loadObj(const std::string& path);
};