#include "render/VertexRender.hpp"
#include "core/types.hpp"
#include "math/matrix.hpp"
#include "math/vector.hpp"
#include "render/triangle.hpp"
#include "render/framebuffer.hpp"
#include "core/config.hpp"
#include <vector>


void VertexRender(uint32_t* fb, Mat4 mvp, Obj &obj) {

    std::vector<Vec3> projected(obj.Vertices.size());

    for (size_t i = 0; i < obj.Vertices.size(); i++) {
        Vec4 clip = transform4(mvp, obj.Vertices[i]);

        float ndcX = clip.x / clip.w;
        float ndcY = clip.y / clip.w;
        float ndcZ = clip.z / clip.w;

        int sx = toScreenX(ndcX);
        int sy = toScreenY(ndcY);

        projected[i] = { (float)sx, (float)sy, ndcZ };
    }

        // -------- DRAW TRIANGLES --------


    for (auto& t : obj.malha) {

        Vec3 v0 = projected[t[0]];
        Vec3 v1 = projected[t[1]];
        Vec3 v2 = projected[t[2]];


        drawTriangle(fb, v0, v1, v2, 0xFF00FF00);
    }
}

// void debug

//     // -------- WIREFRAME DEBUG --------
//     for (int e = 0; e < 12; e++) {
//         int a = cubeEdges[e][0];
//         int b = cubeEdges[e][1];

//         drawLine(
//             framebuffer,
//             projected[a].x, projected[a].y,
//             projected[b].x, projected[b].y,
//             0xFFFFFFFF
//         );
//     }