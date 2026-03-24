#include <iostream>
#include "graphics/Mesh.hpp"

int main() {
    Mesh obj01 = Mesh::loadObj("src/objetos/casa.obj");

    for (const auto& triangulo : obj01.triangles) {
        std::cout << "(";
        std::cout << triangulo.a << ", ";
        std::cout << triangulo.b << ", ";
        std::cout << triangulo.c;
        std::cout << ")";
    }
   
    std::cout << "tamanho do vertice " << obj01.vertices.size() << std::endl;
    
    return 0;
}

