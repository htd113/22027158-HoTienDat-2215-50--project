#include "text.h"
extern App app;
SDL_Texture *score_texture, *Texture, *number_texture;
TTF_Font *font;
void initFonts(void)
{
    std::string base_path = std::string(SDL_GetBasePath());
    font = TTF_OpenFont((base_path+"data/font/Keep Cheese.ttf").c_str(), FONT_SIZE);
    if(font==NULL)
    {
        exit(0);
    }
}

SDL_Color text_color = { 255, 255, 255, 255 };
SDL_Color color = { 255, 0, 0, 255 }; // Red color (R=255, G=0, B=0, A=255)


SDL_Texture *getTexture(const char *text)
{
    SDL_Surface *surface;

    surface = TTF_RenderText_Solid(font, text, color);

    SDL_Texture *texture;

    texture = SDL_CreateTextureFromSurface(app.renderer, surface);
    SDL_FreeSurface(surface); // Free the surface after creating the texture
    //SDL_DestroyTexture()
    return texture;
}

void draw_text(int x, int y, int w, int h, const char *format)
{

    Texture = getTexture(format);

    SDL_Rect dest = {x, y, w, h};

    SDL_RenderCopy(app.renderer, Texture, NULL, &dest);

    SDL_DestroyTexture(Texture);        // Free up texture
}


SDL_Texture *getTextTexture(const char *text)
{
    SDL_Surface *surface;

    surface = TTF_RenderText_Solid(font, text, text_color);

    SDL_Texture *texture;

    texture = SDL_CreateTextureFromSurface(app.renderer, surface);
    SDL_FreeSurface(surface); // Free the surface after creating the texture
    //SDL_DestroyTexture()
    return texture;
}

/* x,y: tọa độ của text
* r: Một con trỏ được tô với giá trị màu đỏ hiện tại
* g: Một con trỏ được tô với giá trị màu xanh lá cây hiện tại
* b: Một con trỏ được tô với giá trị màu xanh hiện tại */
void drawText_score(int x, int y, const char *format, int score)
{
    char numberFormat[256]; 
    
    sprintf(numberFormat, "%06d", score); 

    score_texture = getTextTexture(numberFormat);

    SDL_Rect dest_score = {x/2+SCORE_WIDTH, y, 200, SCORE_HEIGHT};

    SDL_RenderCopy(app.renderer, score_texture, NULL, &dest_score);

    SDL_DestroyTexture(score_texture);        // Free up texture


    Texture = getTextTexture(format);

    SDL_Rect dest = {x, y, SCORE_WIDTH, SCORE_HEIGHT};

    SDL_RenderCopy(app.renderer, Texture, NULL, &dest);

    SDL_DestroyTexture(Texture);        // Free up texture
    
    //SDL_FreeSurface(surfaceMessage);    // Free up surface
}

void drawText_highscore(int x, int y, const char *format, int score)
{

    char numberFormat[256]; 

    sprintf(numberFormat, "%06d", score); 

    score_texture = getTextTexture(numberFormat);

    SDL_Rect dest_score = {HIGHSCORE_WIDTH, y, SCORE_WIDTH, SCORE_HEIGHT};

    SDL_RenderCopy(app.renderer, score_texture, NULL, &dest_score);

    SDL_DestroyTexture(score_texture);
    

    Texture = getTextTexture(format);

    SDL_Rect dest = {x, y, HIGHSCORE_WIDTH, HIGHSCORE_HEIGHT};

    SDL_RenderCopy(app.renderer, Texture, NULL, &dest);

    SDL_DestroyTexture(Texture);        // Free up texture
}

void drawText(int x, int y, int w, int h, const char *format)
{

    Texture = getTextTexture(format);

    SDL_Rect dest = {x, y, w, h};

    SDL_RenderCopy(app.renderer, Texture, NULL, &dest);

    SDL_DestroyTexture(Texture);        // Free up texture
}


void drawText_Highscore(int x, int y, int number, const char *format, int score)
{

    char Number[256];

    sprintf(Number, "N.%02d", number); 

    number_texture = getTextTexture(Number);

    SDL_Rect dest_number = {x, y, SCORE_WIDTH, SCORE_HEIGHT};

    SDL_RenderCopy(app.renderer, number_texture, NULL, &dest_number);

    SDL_DestroyTexture(number_texture);


    char numberFormat[256]; 

    sprintf(numberFormat, "%d", score); 

    score_texture = getTextTexture(numberFormat);

    SDL_Rect dest_score = {x+300, y, SCORE_WIDTH, SCORE_HEIGHT};

    SDL_RenderCopy(app.renderer, score_texture, NULL, &dest_score);

    SDL_DestroyTexture(score_texture);
    

    Texture = getTextTexture(format);

    SDL_Rect dest = {x+70, y, HIGHSCORE_WIDTH*2, HIGHSCORE_HEIGHT};

    SDL_RenderCopy(app.renderer, Texture, NULL, &dest);
    
    SDL_DestroyTexture(Texture);        // Free up texture

}
