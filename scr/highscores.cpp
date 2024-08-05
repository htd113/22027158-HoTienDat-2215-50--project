#include "highscores.h"
 extern App app;
 extern Entity *player;
 Highscores highscores;

void initHighscoreTable(void)
{
    int i;

    memset(&highscores, 0, sizeof(Highscores));

    for (i = 0 ; i < NUM_HIGHSCORES ; i++)
    {
        highscores.highscore[i].score = NUM_HIGHSCORES - i;
    }

}

//bool isPaused = false; // Khai báo biến kiểm tra trạng thái tạm dừng
static void logic(void)
{
    //doBackground();

    //doStarfield();

    if (app.keyboard[SDL_SCANCODE_RETURN])
    {
        initStage();
        //initSounds();
    }

    if (app.keyboard[SDL_SCANCODE_ESCAPE])
    {
        exit(0);
    }
    
    if (app.keyboard[SDL_SCANCODE_SPACE])
    {
        initMenu();
    }

}

static void drawHighscores(void)
{
    int i, y;

    y = 100;

    std::string base_path = std::string(SDL_GetBasePath()); 
    std::ifstream file((base_path + "data/highscore.txt").c_str());
    int k=0, score;
    int arr[8]={0};
    while(file >> score)
    {
        arr[k]=score;
        k++;
    }
    file.close();
    drawText(200, 50, 100, 50, "HIGHSCORES");

    for (i = 0; i < NUM_HIGHSCORES; i++)
    {
        drawText_Highscore(50, y, i+1, "    ................. ", arr[i]);
        y += 50;
    }

    drawText(150, 525, 200, 50, "PRESS [ENTER] TO PLAY!");
}

/*Vẽ ảnh nền*/ 
static void drawBackground(void)
{
    /*Khai báo tệp chứa ảnh nền*/
    SDL_Texture *background = loadTexture("data\\images\\background.jpg");
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
    //drawBackground();

    //drawStarfield();

    if(IsPlayer(player))
    {
        drawBackground();
        drawHighscores();
    } 
}

static int highscoreComparator(const void *a, const void *b)
{
    Highscore *h1 = ((Highscore*)a);
    Highscore *h2 = ((Highscore*)b);

    return h2->score - h1->score;
}

void addHighscore(int score)
{
    Highscore newHighscores[NUM_HIGHSCORES + 1];
    int i;

    for (i = 0 ; i < NUM_HIGHSCORES ; i++)
    {
        newHighscores[i] = highscores.highscore[i];
        newHighscores[i].recent = 0;
    }

    newHighscores[NUM_HIGHSCORES].score = score;
    newHighscores[NUM_HIGHSCORES].recent = 1;

    qsort(newHighscores, NUM_HIGHSCORES + 1, sizeof(Highscore), highscoreComparator);

    for (i = 0 ; i < NUM_HIGHSCORES ; i++)
    {
        highscores.highscore[i] = newHighscores[i];
    }
}



void initHighscores(void)
{
    app.delegate.logic = logic;
    app.delegate.draw = draw;

    memset(app.keyboard, 0, sizeof(int) * MAX_KEYBOARD_KEYS);
}