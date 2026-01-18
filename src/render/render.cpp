#include "render/framebuffer.hpp"
#include "render/culling.hpp"
#include "render/line.hpp"
#include "render/triangle.hpp"
#include "core/config.hpp"
#include <algorithm>
#include <vector>
#include <array>

// FRAMEBUFFER

void putPixel(uint32_t* fb, int x, int y, uint32_t color) {
    if (x < 0 || x >= WIDTH || y < 0 || y >= HEIGHT) return;
    fb[y * WIDTH + x] = color;
};

void clear(uint32_t* fb, uint32_t color) {
    for (int i = 0; i < WIDTH * HEIGHT; i++) {
        fb[i] = color;
    }
};

// DRAW OBJECTS

void drawLine(uint32_t* fb, int x1, int y1, int x2, int y2, uint32_t color) {
    int dx = abs(x2 - x1);
    int dy = abs(y2 - y1);

    int sx = (x1 < x2) ? 1 : -1;
    int sy = (y1 < y2) ? 1 : -1;

    int err = dx - dy;

    while (true) {
        putPixel(fb, x1, y1, color);

        if (x1 == x2 && y1 == y2) break;

        int e2 = 2 * err;

        if (e2 > -dy) {
            err -= dy;
            x1 += sx;
        }
        if (e2 < dx) {
            err += dx;
            y1 += sy;
        }
    }
};

Bary barycentric(float px, float py, float x1, float y1, float x2, float y2, float x3, float y3) {
    float denom = (y2 - y3)*(x1 - x3) + (x3 - x2)*(y1 - y3);

    float a = ((y2 - y3)*(px - x3) + (x3 - x2)*(py - y3)) / denom;
    float b = ((y3 - y1)*(px - x3) + (x1 - x3)*(py - y3)) / denom;
    float c = 1.0f - a - b;

    return {a, b, c};
};

void drawTriangle(uint32_t* fb, Vec3 v1, Vec3 v2, Vec3 v3, uint32_t color) {
    // bounding box
    int minX = std::min({(int)v1.x, (int)v2.x, (int)v3.x});
    int minY = std::min({(int)v1.y, (int)v2.y, (int)v3.y});
    int maxX = std::max({(int)v1.x, (int)v2.x, (int)v3.x});
    int maxY = std::max({(int)v1.y, (int)v2.y, (int)v3.y});

    // clamp
    minX = std::max(minX, 0);
    minY = std::max(minY, 0);
    maxX = std::min(maxX, WIDTH - 1);
    maxY = std::min(maxY, HEIGHT - 1);

    for (int y = minY; y <= maxY; y++) {
        for (int x = minX; x <= maxX; x++) {
            Bary bc = barycentric(x, y, v1.x, v1.y, v2.x, v2.y, v3.x, v3.y);

            if (bc.a >= 0 && bc.b >= 0 && bc.c >= 0) {
                putPixel(fb, x, y, color);
            };
        };
    };
};
