#pragma once
#include <vector>
#include "scene/GameObject.hpp"

class Scene {
public:
    std::vector<GameObject> objects;

    void add(const GameObject& obj);
};