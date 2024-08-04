#include "init.h"

extern App app;
void initSDL(void)
{
    int rendererFlags, windowFlags;

    rendererFlags = SDL_RENDERER_ACCELERATED;

    windowFlags = 0;

    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("Couldn't initialize SDL: %s\n", SDL_GetError());
        exit(1);
    }

    app.window = SDL_CreateWindow(
        "Rapid Roll",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        SCREEN_WIDTH,
        SCREEN_HEIGHT,
        windowFlags
    );
    if (!app.window)
    {
        printf("Failed to open %d x %d window: %s\n", SCREEN_WIDTH, SCREEN_HEIGHT, SDL_GetError());
        exit(1);
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "linear");

    app.renderer = SDL_CreateRenderer(app.window, -1, rendererFlags);

    if (!app.renderer)
    {
        printf("Failed to create renderer: %s\n", SDL_GetError());
        exit(1);
    }

    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("Couldn't initialize SDL Mixer\n");
        exit(1);
    }

    Mix_AllocateChannels(MAX_SND_CHANNELS);

    if (TTF_Init() < 0)
    {
        printf("Couldn't initialize SDL TTF: %s\n", SDL_GetError());
        exit(1);
    }
}

/*tải 1 tệp ảnh theo đường dẫn*/
SDL_Texture* loadTexture(std::string filename) {
    // Get the base path
    std::string base_path = std::string(SDL_GetBasePath());

    SDL_Texture* texture = IMG_LoadTexture(app.renderer, (base_path + filename).c_str());

    return texture;
}

void initGameSystem(void)
{
    initFonts();

    initWidgets();
}

/*static SDL_Texture *getTexture(char *name)
{
    Texture *t;

    for (t = app.textureHead.next ; t != NULL ; t = t->next)
    {
        if (strcmp(t->name, name) == 0)
        {
            return t->texture;
        }
    }

    return NULL;
}

static void addTextureToCache(char *name, SDL_Texture *sdlTexture)
{
    Texture *texture;

    texture = (Texture *)malloc(sizeof(Texture)); // Cast to Texture *
    memset(texture, 0, sizeof(Texture));
    app.textureTail->next = texture;
    app.textureTail = texture;

    STRNCPY(texture->name, name, MAX_NAME_LENGTH);
    texture->texture = sdlTexture;
}

SDL_Texture *loadTexture(char *filename)
{
    SDL_Texture *texture;

    texture = getTexture(filename);

    if (texture == NULL)
    {
        SDL_LogMessage(SDL_LOG_CATEGORY_APPLICATION, SDL_LOG_PRIORITY_INFO, "Loading %s", filename);
        texture = IMG_LoadTexture(app.renderer, filename);
        addTextureToCache(filename, texture);
    }

    return texture;
}
*/
/*void initGame(void)
{
    //initBackground();

    //initStarfield();

    initSounds();

    initFonts();

    initHighscoreTable();

    loadMusic("music/Mercury.ogg");

    playMusic(1);
}*/