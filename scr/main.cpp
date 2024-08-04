#include "stage.h"
//extern dinh nghia app nhieu lan, tranh xung dot

App app;

int main(int argc, char *argv[])
{
    long then;
    float remainder;

    memset(&app, 0, sizeof(App));

    initSDL();

    initGameSystem();

    initDemo();

    initTitle();
    
    long lastFrameTime = SDL_GetTicks();

    //remainder = 0;

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