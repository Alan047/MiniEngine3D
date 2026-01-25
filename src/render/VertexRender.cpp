#pragma once
#include "core/types.hpp"
#include "math/matrix.hpp"
#include "math/vector.hpp"
#include "render/triangle.hpp"
#include "render/framebuffer.hpp"
#include "core/config.hpp"


Vec3 VertexRender(Mat4 mvp, Vec3 objVertices[]) {

Vec3 projected[8];

        for (int i = 0; i < 8; i++) {
            Vec4 clip = transform4(mvp, objVertices[i]);

            float ndcX = clip.x / clip.w;
            float ndcY = clip.y / clip.w;
            float ndcZ = clip.z / clip.w;

            int sx = toScreenX(ndcX);
            int sy = toScreenY(ndcY);

            projected[i] = { (float)sx, (float)sy, ndcZ };
        }

        // -------- DRAW TRIANGLES --------


        for (int t = 0; t < 12; t++) {

            int i0 = cubeTriangles[t][0];
            int i1 = cubeTriangles[t][1];
            int i2 = cubeTriangles[t][2];

            Vec3 v0 = projected[i0];
            Vec3 v1 = projected[i1];
            Vec3 v2 = projected[i2];

            drawTriangle(framebuffer, v0, v1, v2, 0xFF00FF00);
        }
}