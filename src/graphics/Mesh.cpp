#include "graphics/Mesh.hpp"
#include <fstream>
#include <sstream>
#include <iostream>

Mesh Mesh::createCube()
{
    Mesh cube;

    cube.vertices = {
        {-1, -1, -1},
        { 1, -1, -1},
        { 1,  1, -1},
        {-1,  1, -1},
        {-1, -1,  1},
        { 1, -1,  1},
        { 1,  1,  1},
        {-1,  1,  1}
    };

    cube.triangles = {
        // frente (-Z)
    {0,1,2}, {0,2,3},

    // trás (+Z)
    {5,4,7}, {5,7,6},

    // esquerda
    {4,0,3}, {4,3,7},

    // direita
    {1,5,6}, {1,6,2},

    // topo
    {3,2,6}, {3,6,7},

    // base
    {4,5,1}, {4,1,0}
    };

    return cube;
}

Mesh Mesh::createBox(float width,
                     float height,
                     float depth)
{
    Mesh box;

    float w = width ; 
    float h = height;
    float d = depth ; 

    box.vertices = {
        {-w,-h,-d}, { w,-h,-d}, { w, h,-d}, {-w, h,-d},
        {-w,-h, d}, { w,-h, d}, { w, h, d}, {-w, h, d}
    };

    box.triangles = {
        {0,1,2},{0,2,3},
        {4,6,5},{4,7,6},
        {0,3,7},{0,7,4},
        {1,5,6},{1,6,2},
        {3,2,6},{3,6,7},
        {0,4,5},{0,5,1}
    };

    return box;
}

Mesh Mesh::loadObj(const std::string& path)
{
    Mesh obj;
    std::ifstream file(path);
    std::string line;

    while (std::getline(file, line))
    {
        std::stringstream ss(line);
        std::string type;
        ss >> type;

        //VÉRTICES
        if (type == "v") {
            float x, y, z;
            ss >> x >> y >> z;
            obj.vertices.push_back({x, y, z});
            
        }

        //FACES
        else if (type == "f") {
            std::vector<int> indices;
            std::string vert;

            while (ss >> vert) {
                std::stringstream vs(vert);

                int vIndex;
                vs >> vIndex; // pega só o primeiro número antes da /

                indices.push_back(vIndex - 1);
            }

            // triangulação (fan)
            for (int i = 1; i < indices.size() - 1; i++) {
                obj.triangles.push_back({
                    indices[0],
                    indices[i],
                    indices[i + 1]
                });
            }
        }


        
    }
    

    std::cout << path << std::endl;
    
    return obj;

}