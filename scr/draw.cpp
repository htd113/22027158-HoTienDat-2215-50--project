#include "draw.h"

extern App app;



void prepareScene(void)
{
    SDL_SetRenderDrawColor(app.renderer, 255, 93, 0, 0);// renderer đen luon
   
    SDL_RenderClear(app.renderer);
    

}

void presentScene(void)
{
    SDL_RenderPresent(app.renderer);
}

void blit_player(SDL_Texture* texture, int x, int y)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = PLAYER_WIDTH;
    dest.h = PLAYER_HEIGHT;

    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}

void blit_board(SDL_Texture* texture, int x, int y)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = BOARD_WIDTH;
    dest.h = BOARD_HEIGHT;

    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}
