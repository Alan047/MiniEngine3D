#include <SDL2/SDL.h>
#include <cstdint>
#include <iostream>

#include "core/config.hpp"
#include "core/types.hpp"

#include "math/matrix.hpp"
#include "math/vector.hpp"

#include "render/framebuffer.hpp"
#include "render/line.hpp"
#include "render/triangle.hpp"
#include "render/culling.hpp"

#include "scene/cube.hpp"


int main(int argc, char* argv[]) {

    // ======================
    // SDL INIT
    // ======================
    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow(
        "Rasterizador 3D",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        WIDTH, HEIGHT,
        0
    );

    SDL_Renderer* renderer =
        SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_Texture* texture =
        SDL_CreateTexture(
            renderer,
            SDL_PIXELFORMAT_ARGB8888,
            SDL_TEXTUREACCESS_STREAMING,
            WIDTH, HEIGHT
        );


    // ======================
    // CAMERA & PROJECTION
    // ======================
    Vec3 cameraPos = {0, 0, 0};
    Vec3 cameraTarget = {0, 0, -1};
    Vec3 cameraUp = {0, 1, 0};

    float fov = 70.0f * 3.1415926f / 180.0f;
    float aspect = float(WIDTH) / float(HEIGHT);
    Mat4 projection = perspectiva(fov, aspect, 0.1f, 100.0f);

    // ======================
    // LOOP
    // ======================
    bool running = true;
    SDL_Event event;

    float angle = 0.0f;

    while (running) {

        // -------- EVENTS --------
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT)
                running = false;
        }

        // -------- UPDATE --------
        angle += 0.001f;

        Mat4 model = translacao(0, 0, 6) * rotacaoY(angle);
        Mat4 view  = look(cameraPos, cameraTarget, cameraUp);
        Mat4 mvp   = projection * view * model;

        // -------- CLEAR --------
        clear(framebuffer, 0xFF202020);

        // -------- PROJECT VERTICES --------
        

        // -------- WIREFRAME DEBUG --------
        for (int e = 0; e < 12; e++) {
            int a = cubeEdges[e][0];
            int b = cubeEdges[e][1];

            drawLine(
                framebuffer,
                projected[a].x, projected[a].y,
                projected[b].x, projected[b].y,
                0xFFFFFFFF
            );
        }

        // -------- PRESENT --------
        SDL_UpdateTexture(texture, nullptr,
                          framebuffer, WIDTH * sizeof(uint32_t));

        SDL_RenderClear(renderer);
        SDL_RenderCopy(renderer, texture, nullptr, nullptr);
        SDL_RenderPresent(renderer);
    }

    // ======================
    // CLEANUP
    // ======================
    delete[] framebuffer;
    SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}
