#ifndef TEXT_H
#define TEXT_H

#include "stage.h"

void initFonts(void);

SDL_Texture *getTexture(const char *text);

void draw_text(int x, int y, int w, int h, const char *format);

SDL_Texture *getTextTexture(const char *text);

//SDL_Texture *toTexture(SDL_Surface *surface, int destroySurface);
void drawText_score(int x, int y, const char *format, int score);

void drawText_highscore(int x, int y, const char *format, int score);

void drawText(int x, int y, int w, int h, const char *format);

void drawText_Highscore(int x, int y, int number, const char *format, int score);


#endif