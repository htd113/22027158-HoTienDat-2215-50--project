#include "demo.h"
extern App app;
static void draw(void)
{
    drawWidgets();
}

static void logic(void)
{
    doWidgets();
}

void initDemo(void)
{
    Widget *w;
    int x;

    x = 500;

    w = createWidget("start");
    w->x = x;
    w->y = 200;
    strcpy(w->label, "Start");

    app.activeWidget = w;

    w = createWidget("load");
    w->x = x;
    w->y = 250;
    strcpy(w->label, "Load");

    w = createWidget("options");
    w->x = x;
    w->y = 300;
    strcpy(w->label, "Options");

    w = createWidget("credits");
    w->x = x;
    w->y = 350;
    strcpy(w->label, "Credits");

    w = createWidget("exit");
    w->x = x;
    w->y = 400;
    strcpy(w->label, "Exit");

    app.delegate.logic = &logic;
    app.delegate.draw = &draw;
}