#ifndef DRAW_H
#define DRAW_H

#include <bits/stdc++.h>
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include "structs.h"


SDL_Texture* loadTexture(std::string filename);

void prepareScene(void);

void presentScene(void);

void blit_player(SDL_Texture* texture, int x, int y);

void blit_board(SDL_Texture* texture, int x, int y);

#endif