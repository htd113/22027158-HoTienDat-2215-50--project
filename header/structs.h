#ifndef STRUCTS_H
#define STRUCTS_H

#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "defs.h"

struct Widget {
    float x;
    float y;
    int w;
    int h;
    float dx;
    float dy;
    int reload;
    SDL_Texture *texture;
    Widget *next;
    
};

typedef struct{
    Widget widgetHead, *widgetTail;
} Menu;

/*typedef struct {
    void (*logic)(void);
    void (*draw)(void);
} Delegate;*/


typedef struct {
    struct {
        void (*logic)(void);
        void (*draw)(void);
    } delegate;
    SDL_Renderer *renderer;
    SDL_Window *window;
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
    //int health[MAX_HEARTS];
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
    //Entity widgetHead, *widgetTail;
    int score;
} Stage;

typedef struct {
    int recent;
    int score;
} Highscore;

typedef struct {
    Highscore highscore[NUM_HIGHSCORES];
} Highscores;



#endif 