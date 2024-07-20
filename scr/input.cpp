#include <bits/stdc++.h>
#include "SDL2/SDL.h"
#include"structs.h"
extern App app;
void doKeyDown(SDL_KeyboardEvent *event)
{
    if (event->repeat == 0)
    {
        

        if (event->keysym.scancode == SDL_SCANCODE_LEFT)
        {
            app.left = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
        {
            app.right = 1;
        }
    }
}

void doKeyUp(SDL_KeyboardEvent *event)
{
    if (event->repeat == 0)
    {
        

        if (event->keysym.scancode == SDL_SCANCODE_LEFT)
        {
            app.left = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_RIGHT)
        {
            app.right = 0;
        }
    }
}

void doInput(void)
{
    SDL_Event event;

    while (SDL_PollEvent(&event))
    {
        switch (event.type)
        {
            case SDL_QUIT:
                exit(0);
                break;

            case SDL_KEYDOWN:
                doKeyDown(&event.key);
                break;
            
            case SDL_KEYUP:
                doKeyUp(&event.key);
                break;


            default:
                break;
        }
    
    }   
}