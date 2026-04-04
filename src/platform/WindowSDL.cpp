#include "platform/WindowSDL.hpp"
#include <iostream>

Window_SDL::Window_SDL(int width, int height)

    // SDL_Init inicia a SDL
    // Verifica de houve erro nainciação da SDL
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        std::cout << "Erro ao iniciar SDL\n";
    }

    //Cria Janela SDL

    window = SDL_CreateWindow(
        "MiniEngine3D",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        width,
        height,
        0
    );

    SDL_SetRelativeMouseMode(SDL_TRUE);

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
}

Window_SDL::~Window_SDL()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

// Método que capitura os eventos da janela SDL

bool Window_SDL::pollEvents()
{
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT)
            return false;
    }

    return true;
}

SDL_Renderer* Window_SDL::getRenderer()
{
        return renderer;
}