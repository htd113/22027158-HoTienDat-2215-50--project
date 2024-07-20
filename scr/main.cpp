#include <bits/stdc++.h>
#include "SDL2/SDL.h"
#include <SDL2/SDL_image.h>
#include "structs.h"
#include "defs.h"
#include "draw.h"
#include "init.h"
#include "input.h"


App app;
Entity player;


int main(int argc, char** argv)
{
    memset(&app, 0, sizeof(App));
    memset(&player, 0, sizeof(Entity));
    
    initSDL();

    player.x = 100;
    player.y = 100;
    player.texture = loadTexture("data/images/monster.jpg");
 
    while (true)
    {
        prepareScene();

        doInput();

        if (app.left && player.x>=0)
        {
            player.x -= PLAYER_SPEED;
        }

        if (app.right && player.x<=1180)
        {
            player.x += PLAYER_SPEED;
        }

        blit(player.texture, player.x, player.y);

        presentScene();

        SDL_Delay(16);

    }

    return 0;
}