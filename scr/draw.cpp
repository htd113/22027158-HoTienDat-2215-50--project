#include "draw.h"

extern App app;

void prepareScene(void)
{
    SDL_SetRenderDrawColor(app.renderer, 255, 255, 255, 0);

    SDL_RenderClear(app.renderer);


}

void presentScene(void)
{
    SDL_RenderPresent(app.renderer);
}

void blit(SDL_Texture* texture, int x, int y) {
    int textureWidth, textureHeight;
    // Tạo một hình chữ nhật để xác định vị trí vẽ
    SDL_Rect destinationRect = { x, y, textureWidth, textureHeight };

    // Vẽ texture lên màn hình
    SDL_RenderCopy(app.renderer, texture, NULL, &destinationRect);
}


void blitScaled(SDL_Texture* texture, int x, int y, int w, int h)
{
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = w;
    dest.h = h;

    SDL_RenderCopy(app.renderer, texture, NULL, &dest);
}


void blitRotated(SDL_Texture* texture, int x, int y, double angle)
{
    // Get the texture dimensions
    int textureWidth, textureHeight;
    SDL_QueryTexture(texture, NULL, NULL, &textureWidth, &textureHeight);

    // Calculate the center point for rotation
    int centerX = x + textureWidth / 2;
    int centerY = y + textureHeight / 2;

    // Create a destination rectangle
    SDL_Rect dest;
    dest.x = x;
    dest.y = y;
    dest.w = textureWidth;
    dest.h = textureHeight;

    // Render the rotated texture
    SDL_RenderCopyEx(app.renderer, texture, NULL, &dest, angle, NULL, SDL_FLIP_NONE);
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

void blitRect(SDL_Texture* texture, SDL_Rect* src, int x, int y)
{
    SDL_Rect dest;

    dest.x = x;
    dest.y = y;
    dest.w = src->w;
    dest.h = src->h;

    SDL_RenderCopy(app.renderer, texture, src, &dest);
}