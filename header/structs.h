#include <bits/stdc++.h>
#include "SDL2/SDL.h"
typedef struct
{
    SDL_Renderer* renderer;
    SDL_Window* window;
    int up;
    int down;
    int left;
    int right;

}App;

typedef struct
{
    int x;
    int y;
    int dx;
    int dy;
    int health;
    SDL_Texture* texture;
} Entity;

App app;
Entity player;