#pragma once
#include <SDL2/SDL.h>
#include <cstdint>
#include "math/Mat4.hpp"
#include "math/Vec3.hpp"

class SoftwareRenderer {
public:
    SoftwareRenderer(SDL_Renderer* renderer,
                     int width,
                     int height);

    ~SoftwareRenderer();

    void clear(uint32_t color);
    void present();
    void drawPixel(int x, int y, uint32_t color);
    Vec3 project(const Vec3& point, const Mat4& mvp);
    void drawLine(int x0, int y0, int x1, int y1, uint32_t color);
    void drawTriangle(const Vec3& v0, const Vec3& v1, const Vec3& v2, uint32_t color);

private:
    SDL_Renderer* renderer;
    SDL_Texture* texture;

    uint32_t* framebuffer;
    float* zbuffer;

    int width;
    int height;
};