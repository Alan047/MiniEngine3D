#pragma once
#include "scene/Transform.hpp"
#include "graphics/Mesh.hpp"
#include <cstdint>


class GameObject {
public:
    Transform transform;
    Mesh* mesh;
    uint32_t color;

    Mesh CarregarMesh(const std::string& path);
};