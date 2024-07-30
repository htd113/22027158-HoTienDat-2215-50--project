#ifndef STRUCTS_H
#define STRUCTS_H

#include"defs.h"
typedef struct {
    void (*logic)(void);
    void (*draw)(void);
} Delegate;

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    Delegate delegate;
    //int left,right,down,up;
    int keyboard[MAX_KEYBOARD_KEYS];
} App;

struct Entity {
    float x;
    float y;
    int w;
    int h;
    float dx;
    float dy;
    float gravitySpeed; // Tốc độ rơi
    int health[MAX_HEARTS];
    int reload;
    int side;
    int lifetime;
    SDL_Texture *texture;
    Entity *next;
};

typedef struct {
    Entity enemyHead, *enemyTail;
    //Entity boardHead, *boardTail;
    Entity heartHead, *heartTail;
} Stage;

#endif 