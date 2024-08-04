#include "title.h"
extern App app;
SDL_Texture *sdl2Texture, *shooterTexture;

static void drawLogo(void)
{

    drawText(SCREEN_WIDTH/2-100, SCREEN_HEIGHT/2-50, 200, 50, "RAPID ROLL");

}

static void drawBackground(void)
{
    /*Khai báo tệp chứa ảnh nền*/
    SDL_Texture *background = loadTexture("data\\images\\cxok.jpg");
    SDL_Rect dest = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(app.renderer, background, NULL, &dest);
    /*SDL_Rect dest;
    int x;

    for (x = backgroundX ; x < SCREEN_WIDTH ; x += SCREEN_WIDTH)
    {
        dest.x = x;
        dest.y = 0;
        dest.w = SCREEN_WIDTH;
        dest.h = SCREEN_HEIGHT;

        SDL_RenderCopy(app.renderer, background, NULL, &dest);
    }*/
}

static void draw(void)
{
    drawBackground();

    //drawStarfield();

    drawLogo();

}

static void logic(void)
{
    //doBackground();

    //doStarfield();
    //SDL_Delay(3000);
    if(app.keyboard[SDL_SCANCODE_RETURN])
    {
        initHighscores();

        initStage();

        initSounds();
    }
}

void initTitle(void)
{
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);



}