#include "scene/GameObject.hpp"

// Mesh GameObject::CarregarMesh(const std::string& path) {
//     return &Mesh::loadObj(path);
    
// }

GameObject::GameObject() :  color(0xFFFFFFFF),
                            mesh(Mesh::createCube()) {
    
    
}

GameObject::GameObject(int op) :color(0xFFFFFFFF) {
    if (op == 1 ) {
        transform.rotation.y += 0.001f;
    }
}