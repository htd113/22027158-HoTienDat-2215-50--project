#include "stage.h"
//extern dinh nghia app nhieu lan, tranh xung dot

App app;

int main(int argc, char *argv[])
{
    memset(&app, 0, sizeof(App));

    initSDL();

    initFonts();

    initTitle();
    
    long lastFrameTime = SDL_GetTicks();

    while (1)
    {
        prepareScene();

        doInput();   

        app.delegate.logic();

        app.delegate.draw();

        presentScene();

        capFrameRate(&lastFrameTime);
    }

    
    return 0;
}