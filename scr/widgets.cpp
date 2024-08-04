#include "widgets.h"
extern App app;
Widget widgetHead, *widgetTail;


void drawWidgets(void)
{
    Widget *w;
    SDL_Color c;

    for (w = widgetHead.next ; w != NULL ; w = w->next)
    {
        if (w == app.activeWidget)
        {
            c.g = 255;
            c.r = c.b = 0;

            drawText( w->x - 40, w->y, SCORE_WIDTH, SCORE_HEIGHT, "TEXT_ALIGN_LEFT");
        }
        else
        {
            c.r = c.g = c.b = 255;
        }

        drawText(w->x, w->y, SCORE_WIDTH, SCORE_HEIGHT,  "TEXT_ALIGN_LEFT");
    }
}

void doWidgets(void)
{
    if (app.keyboard[SDL_SCANCODE_UP])
    {
        app.keyboard[SDL_SCANCODE_UP] = 0;

        app.activeWidget = app.activeWidget->prev;

        if (app.activeWidget == &widgetHead)
        {
            app.activeWidget = widgetTail;
        }
    }

    if (app.keyboard[SDL_SCANCODE_DOWN])
    {
        app.keyboard[SDL_SCANCODE_DOWN] = 0;

        app.activeWidget = app.activeWidget->next;

        if (app.activeWidget == NULL)
        {
            app.activeWidget = widgetHead.next;
        }
    }
}

Widget* createWidget(const char* Name)
{
    Widget* w = (Widget*)malloc(sizeof(Widget));
    if (w)
    {
        w->prev = widgetTail;
        w->next = NULL; // Initialize next pointer
        widgetTail->next = w;
        widgetTail = w;

        // Assuming 'name' is a null-terminated string
        strcpy(w->name, Name);
    }
    return w;
}


void initWidgets(void)
{
    memset(&widgetHead, 0, sizeof(Widget));
    widgetTail = &widgetHead;
}
