#ifndef INPUT_H
#define INPUT_H

#include <bits/stdc++.h>
#include "SDL2/SDL.h"

void doKeyDown(SDL_KeyboardEvent *event);

void doKeyUp(SDL_KeyboardEvent *event);

void doInput(void);


#endif