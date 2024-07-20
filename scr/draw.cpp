#include <bits/stdc++.h>
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include "structs.h"

extern App app;



void prepareScene(void)
{
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 0);// renderer đen luon
   
    SDL_RenderClear(app.renderer);
    

}

void presentScene(void)
{
    SDL_RenderPresent(app.renderer);
}

void blit(SDL_Texture* texture, int x, int y)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w=100;
    dest.h=100;

    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}