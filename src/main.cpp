
#include <SDL2/SDL.h>
#include <iostream>


int main(int argc, char* argv[]) {

    SDL_Init(SDL_INIT_VIDEO);

    SDL_Window* window = SDL_CreateWindow("SLD2", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
    
    bool rodando = true;

    SDL_Event evento;

    while(rodando) {
        while(SDL_PollEvent(&evento)) {
            if(evento.type == SDL_QUIT) {
                rodando = false;
            };
        };
    };

    SDL_DestroyWindow(window);
    SDL_Quit();

    

    std::cout << "Hello Worde" << std::endl;
    return 0;
};