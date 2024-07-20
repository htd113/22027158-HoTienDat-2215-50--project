#ifndef STRUCTS_H
#define STRUCTS_H

typedef struct {
    SDL_Renderer *renderer;
    SDL_Window *window;
    int left;
    int right;

} App;

typedef struct {
    int x;
    int y;
    SDL_Texture *texture;
} Entity;

#endif 