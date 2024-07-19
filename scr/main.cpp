#include <bits/stdc++.h>
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include "structs.h"
#include"defs.h"
#include"input.h"

void initSDL(void)
{
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED;

    windowFlags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    app.window = SDL_CreateWindow(
        "Rapid Roll",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        windowFlags
    );
    if (!app.window)
    {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

    if (!app.renderer)
    {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }
}
/*
void doKeyDown(SDL_KeyboardEvent *event)
{
    if (event->repeat == 0)
    {
        if (event->keysym.scancode == SDL_SCANCODE_UP)
        {
            app.up = 1;
        }

        if (event->keysym.scancode == SDL_SCANCODE_DOWN)
        {
            app.down = 1;
        }

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
        if (event->keysym.scancode == SDL_SCANCODE_UP)
        {
            app.up = 0;
        }

        if (event->keysym.scancode == SDL_SCANCODE_DOWN)
        {
            app.down = 0;
        }

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
*/
SDL_Texture* background()
{
    std::string base_path = std::string(SDL_GetBasePath());
    SDL_Texture* background = IMG_LoadTexture(app.renderer, (base_path + "data/images/background.jpg").c_str());

    return background;
}

SDL_Texture* loadTexture(std::string path) {
    // Get the base path
    std::string base_path = std::string(SDL_GetBasePath());

    // Load the image as a surface first
    SDL_Surface* loadedSurface = IMG_Load((base_path + path).c_str());
    if (loadedSurface == nullptr) {
        std::cerr << "Unable to load image " << path << "! SDL_image Error: " << IMG_GetError() << std::endl;
        return nullptr;
    }

    // Set the color key for transparency
    SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

    // Create texture from surface
    SDL_Texture* texture = SDL_CreateTextureFromSurface(app.renderer, loadedSurface);
    if (texture == nullptr) {
        std::cerr << "Unable to create texture from " << path << "! SDL Error: " << SDL_GetError() << std::endl;
    }

    // Free the loaded surface
    SDL_FreeSurface(loadedSurface);

    return texture;
}

void prepareScene(void)
{
    SDL_SetRenderDrawColor(app.renderer, 0, 0, 0, 0);// renderer đen luon
    //SDL_RenderCopy(app.renderer, background(), NULL, NULL);
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


void speed(void)
{
    if (app.up && player.y >=0)
    {
        player.y -= PLAYER_SPEED;
    }

    if (app.down && player.y<=620)
    {
        player.y += PLAYER_SPEED;
    }

    if (app.left && player.x>=0)
    {
        player.x -= PLAYER_SPEED;
    }

    if (app.right && player.x<=1180)
    {
        player.x += PLAYER_SPEED;
    }

}

int main(int argc, char** argv)
{
    memset(&app, 0, sizeof(App));
    memset(&player, 0, sizeof(Entity));
    //memset(&bullet, 0, sizeof(Entity));
    initSDL();

    player.x = 100;
    player.y = 100;
    player.texture = loadTexture("data/images/monster.jpg");
    //bullet.texture = loadTexture(s);
    while (true)
    {
        prepareScene();

        doInput();

        player.x += player.dx;
        player.y += player.dy;

        speed();

        blit(player.texture, player.x, player.y);

        presentScene();

        SDL_Delay(16);

    }

    return 0;
}