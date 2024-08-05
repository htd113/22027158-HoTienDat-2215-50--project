#include "menu.h"
extern App app;
Menu menu;
//int highscore;
Widget* pointer;

static void initPointer()
{
    pointer = (Widget*)malloc(sizeof(Widget));
    if (!pointer)
    {
        fprintf(stderr, "Failed to allocate memory for pointer\n");
        exit(1);
    }
    memset(pointer, 0, sizeof(Widget));
    menu.widgetTail->next = pointer;
    menu.widgetTail = pointer;

    pointer->x = 150;
    pointer->y = 200;

    pointer->texture = getTexture(">");
    if (!pointer->texture)
    {
        fprintf(stderr, "Failed to load pointer texture: %s\n", SDL_GetError());
        exit(1);
    }
    SDL_QueryTexture(pointer->texture, NULL, NULL, &pointer->w, &pointer->h);

   
}

/*Xử lý logic di chuyển của người chơi dựa trên đầu vào từ bàn phím.
cập nhật vị trí của người chơi dựa trên tốc độ di chuyển.*/
static void doPointer(void)
{
   
        pointer->dx = pointer->dy = 0;

        if (pointer->reload > 0)
        {
            pointer->reload--;
        }

        if (app.keyboard[SDL_SCANCODE_UP] && pointer->y >= 200 )
        {
            pointer->dy = -POINTER_SPEED;
            //playSound(SND_PLAYER_MOVE, CH_PLAYER);
        }

        if (app.keyboard[SDL_SCANCODE_DOWN] && pointer->y <= 350)
        {
            pointer->dy = POINTER_SPEED;
            //playSound(SND_PLAYER_MOVE, CH_PLAYER);
        }



        pointer->x+=pointer->dx;
        pointer->y+=pointer->dy;
    

}

static void drawPointer(void)
{
    draw_text(pointer->x, pointer->y, 50, 50, ">");
}

static void drawBackground(void)
{
    /*Khai báo tệp chứa ảnh nền*/
    SDL_Texture *background = loadTexture("data\\images\\background.jpg");
    SDL_Rect dest = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT};
    SDL_RenderCopy(app.renderer, background, NULL, &dest);
}
static bool soundEnabled = true;
static void draw(void)
{
    drawBackground();

    drawText(200, 50, 100, 70, "MENU");

    drawText(200, 200, 100, 50, "START");

    //drawText(200, 200, 100, 50, "REMUSE");
    drawText(200, 275, 100, 50, "SOUND");
    if(soundEnabled) drawText(300, 275, 50, 50, ":ON");
    else drawText(300, 275, 50, 50, ":OFF");
    //drawText(200, 300, 100, 50, "TUTORIAL");

    drawText(200, 350, 100, 50, "QUIT");
    drawPointer();
    //drawText(150, 150, 50, 50, ">");
}

static void toggleSound(void)
{
    soundEnabled = !soundEnabled;
}

static void logic(void)
{

    doPointer();

    //START
    if(pointer->y >=200 && pointer->y <250)
    {
        if (app.keyboard[SDL_SCANCODE_RETURN])
        {
            initHighscores();

            initStage();

            if(soundEnabled) initSounds();
        }
    }

    //SOUND
    else if(pointer->y >=275 && pointer->y <325)
    {
        if (app.keyboard[SDL_SCANCODE_RETURN])
        {
            toggleSound();
        }
    }

    //QUIT
    else if(pointer->y >= 350)
    {
        if (app.keyboard[SDL_SCANCODE_RETURN])
        {
            exit(0);
        }
    }
}

void initMenu(void)
{
    
    app.delegate.logic = &logic;
    app.delegate.draw = &draw;
    memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
    memset(&menu, 0, sizeof(Menu));
    menu.widgetTail = &menu.widgetHead;

    initPointer();
}