#include "title.h"
extern App app;
SDL_Texture *sdl2Texture, *shooterTexture;

static void drawLogo(void)
{

    drawText(SCREEN_WIDTH/2-150, SCREEN_HEIGHT/2-100, 200, 50, "RAPID ROLL");
    drawText(SCREEN_WIDTH/2-175, SCREEN_HEIGHT/2+200, 300, 20, "PRESS [ENTER] TO MENU!!");

}

static void drawBackground(void)
{
    /*Khai báo tệp chứa ảnh nền*/
    SDL_Texture *background = loadTexture("data\\images\\cxok.jpg");
    SDL_Rect dest = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(app.renderer, background, NULL, &dest);
    SDL_DestroyTexture(background);
}

static void draw(void)
{
    drawBackground();

    //drawStarfield();

    drawLogo();

}

static void logic(void)
{
    if(app.keyboard[SDL_SCANCODE_RETURN])
    {
        initMenu();
    }
}

void initTitle(void)
{
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);



}