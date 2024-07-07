#include <bits/stdc++.h>
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
int main(int argc, char** argv)
{
    if (SDL_Init(SDL_INIT_EVERYTHING))
    {
        printf("Cant init sdl\n");
    }
    SDL_Window* window = SDL_CreateWindow(
        "test sdl program",
        SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
        1200, 800,
        0
    );

    SDL_Renderer* renderer = SDL_CreateRenderer(
        window,
        -1,
        SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC
    );

    std::string base_path = std::string(SDL_GetBasePath());

    SDL_Texture* memory = IMG_LoadTexture(renderer, (base_path + "data/images/aa.png").c_str());

    while (true)
    {
        SDL_Event e;
        while (SDL_PollEvent(&e))
        {
            if (e.type == SDL_QUIT)
            {
                SDL_DestroyWindow(window);
                SDL_DestroyRenderer(renderer);
                SDL_Quit();
                exit(0);
            }
        }

        SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
        SDL_RenderClear(renderer);
        SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
        SDL_RenderDrawLine(renderer, 20, 20, 50, 50);

        SDL_Rect rect = { 50,50,100,200 };
        SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);  
        SDL_RenderFillRect(renderer, &rect);

        SDL_RenderCopy(renderer, memory, NULL, NULL);

        SDL_RenderPresent(renderer);

        SDL_Delay(20);
    }
    return 0;
}