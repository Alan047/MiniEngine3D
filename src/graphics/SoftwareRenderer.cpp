#include "graphics/SoftwareRenderer.hpp"
#include <algorithm>



SoftwareRenderer::SoftwareRenderer(SDL_Renderer* renderer,
                                   int width,
                                   int height)
    : renderer(renderer),
      width(width),
      height(height)
{
    // cria textura para desenhar pixels
    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_ARGB8888,
        SDL_TEXTUREACCESS_STREAMING,
        width,
        height
    );

    // aloca framebuffer
    framebuffer = new uint32_t[width * height];
}

SoftwareRenderer::~SoftwareRenderer()
{
    delete[] framebuffer;
    SDL_DestroyTexture(texture);
}

void SoftwareRenderer::clear(uint32_t color)
{
    for (int i = 0; i < width * height; i++)
    {
        framebuffer[i] = color;
    }
}

void SoftwareRenderer::present()
{
    // envia framebuffer para textura
    SDL_UpdateTexture(
        texture,
        nullptr,
        framebuffer,
        width * sizeof(uint32_t)
    );

    SDL_RenderClear(renderer);
    SDL_RenderCopy(renderer, texture, nullptr, nullptr);
    SDL_RenderPresent(renderer);
}

void SoftwareRenderer::drawPixel(int x, int y, uint32_t color)
{
    // Clipping (muito importante)
    if (x < 0 || x >= width || y < 0 || y >= height)
        return;

    framebuffer[y * width + x] = color;
}

Vec3 SoftwareRenderer::project(const Vec3& point,
                                const Mat4& mvp)
{
    Vec4 v(point.x, point.y, point.z, 1.0f);
    Vec4 projected = mvp * v;

    // evitar divisão inválida
    if (projected.w == 0.0f)
        return {0,0,0};

    // evitar pontos atrás da câmera
    if (projected.w < 0.01f)
        return {0,0,0};

    projected.x /= projected.w;
    projected.y /= projected.w;
    projected.z /= projected.w;

    float screenX = (projected.x + 1.0f) * 0.5f * width;
    float screenY = (1.0f - projected.y) * 0.5f * height;

    return { screenX, screenY, projected.z };
}

void SoftwareRenderer::drawLine(int x0, int y0,
                                int x1, int y1,
                                uint32_t color)
{
    int dx = abs(x1 - x0);
    int dy = abs(y1 - y0);

    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;

    int err = dx - dy;

    while (true)
    {
        drawPixel(x0, y0, color);

        if (x0 == x1 && y0 == y1)
            break;

        int e2 = 2 * err;

        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }

        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

static float edgeFunction(const Vec3& a, const Vec3& b, const Vec3& c) 
{
    return (c.x - a.x) * (b.y - a.y)
         - (c.y - a.y) * (b.x - a.x);
}

void SoftwareRenderer::drawTriangle(const Vec3& v0,
                                    const Vec3& v1,
                                    const Vec3& v2,
                                    uint32_t color)
{
    int minX = std::min({ (int)v0.x, (int)v1.x, (int)v2.x });
    int maxX = std::max({ (int)v0.x, (int)v1.x, (int)v2.x });
    int minY = std::min({ (int)v0.y, (int)v1.y, (int)v2.y });
    int maxY = std::max({ (int)v0.y, (int)v1.y, (int)v2.y });

    minX = std::max(minX, 0);
    minY = std::max(minY, 0);
    maxX = std::min(maxX, width - 1);
    maxY = std::min(maxY, height - 1);

    float area = edgeFunction(v0, v1, v2);
    if (area == 0) return;

    for (int y = minY; y <= maxY; y++)
    {
        for (int x = minX; x <= maxX; x++)
        {
            Vec3 p = { (float)x, (float)y, 0 };

            float w0 = edgeFunction(v1, v2, p);
            float w1 = edgeFunction(v2, v0, p);
            float w2 = edgeFunction(v0, v1, p);

            // aceita ambos os sentidos
            if ((w0 >= 0 && w1 >= 0 && w2 >= 0) ||
                (w0 <= 0 && w1 <= 0 && w2 <= 0))
            {
                drawPixel(x, y, color);
            }
        }
    }
}

// Funções Auxiliares

