#pragma once
#include <SDL2/SDL.h>

class Window_SDL {
public:
    Window_SDL(int width, int height);
    ~Window_SDL();

    bool pollEvents();

    SDL_Renderer* getRenderer();

private:

    //Recebe a jenela SDL
    
    SDL_Window* window;
    SDL_Renderer* renderer;
};