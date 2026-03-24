#include "scene/Scene.hpp"

void Scene::add(const GameObject& obj)
{
    objects.push_back(obj);
}