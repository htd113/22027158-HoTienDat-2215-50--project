#ifndef INIT_H
#define INIT_H

#include <bits/stdc++.h>
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include "structs.h"
#include"defs.h"


void initSDL(void);
SDL_Texture* loadTexture(std::string filename) ;

#endif