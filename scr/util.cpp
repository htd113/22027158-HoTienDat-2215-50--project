#include "util.h"
extern Stage stage;
/* Xử lý va chạm giữa người chơi và kẻ thù*/
void handleCollisions(Entity* player, Entity* enemy) {
    SDL_Rect playerRect = { static_cast<int>(player->x), 
                            static_cast<int>(player->y), 
                            PLAYER_WIDTH, 
                            PLAYER_HEIGHT 
                            };

    SDL_Rect enemyRect = { static_cast<int>(enemy->x), 
                            static_cast<int>(enemy->y), 
                            BOARD_WIDTH, 
                            BOARD_HEIGHT 
                            };

    if (SDL_HasIntersection(&playerRect, &enemyRect)) {
        player->y = enemy->y;
        player->y += enemy->dy;
        //stage.score+=10;
        
        
        
    }
}

int IsPlayer(Entity *player)
{
    if (  player->y < 0 || player->y > SCREEN_HEIGHT) 
    {
        return 1;
    }
    return 0;
}
/* Xử lý va chạm giữa người chơi và trái tim*/
/*void handle_Collisions(Entity* player, Entity* heart) {
    SDL_Rect playerRect = { static_cast<int>(player->x), 
                            static_cast<int>(player->y), 
                            PLAYER_WIDTH, 
                            PLAYER_HEIGHT 
                            };

    SDL_Rect heartRect = { static_cast<int>(heart->x), 
                            static_cast<int>(heart->y), 
                            HEART_WIDTH, 
                            HEART_HEIGHT 
                            };

    if (SDL_HasIntersection(&playerRect, &heartRect)) {
        // Đặt vị trí người chơi trước kẻ thù
        //player->x = enemy->x;
        player->health++;
        heart->active = 0;
    }
}
*/