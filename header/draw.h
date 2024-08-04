#ifndef DRAW_H
#define DRAW_H

#include <bits/stdc++.h>
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include "structs.h"


SDL_Texture* loadTexture(std::string filename);

void prepareScene(void);

void presentScene(void);

void blit(SDL_Texture* texture, int x, int y);

void blitScaled(SDL_Texture* texture, int x, int y, int w, int h);

void blitRotated(SDL_Texture* texture, int x, int y, double angle);

void blit_player(SDL_Texture* texture, int x, int y);

void blit_board(SDL_Texture* texture, int x, int y);

void blitRect(SDL_Texture *texture, SDL_Rect *src, int x, int y);

#endif