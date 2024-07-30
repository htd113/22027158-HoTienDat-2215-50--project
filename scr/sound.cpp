#include "init.h"
/*
Mix_Chunk* sounds[MAX_SND_CHANNELS];
Mix_Music* music = NULL;

Mix_Chunk* loadMusic(std::string filename) {
    // Get the base path
    std::string base_path = std::string(SDL_GetBasePath());

    Mix_Chunk* music = Mix_LoadWAV( (base_path + filename).c_str());

    return music;
}

void loadMusic(const std::string& filename) 
{
    if (music != NULL) 
    {
        Mix_HaltMusic();
        Mix_FreeMusic(music);
        music = NULL;
    }
    std::string base_path = std::string(SDL_GetBasePath());
    music = Mix_LoadMUS((base_path + filename).c_str());
    if (music == NULL) 
    {
        printf("Error loading music: %s\n", Mix_GetError());
        // Xử lý lỗi tại đây (ví dụ: thoát khỏi chương trình)
        exit(0);
    }
}

void loadSounds(void) 
{
    sounds[SND_PLAYER_DIE] = loadMusic("data\\audio\\player_die.mp3");
    sounds[SND_PLAYER_MOVE] = loadMusic("data\\audio\\player_move.mp3");
    // Khởi tạo các âm thanh khác ở đây (nếu cần)
}

void initSounds(void)
{
    memset(sounds, 0, sizeof(Mix_Chunk*) * SND_MAX);

    music = NULL;

    loadSounds();
}

void playMusic(int loop) 
{
    Mix_PlayMusic(music, (loop) ? -1 : 0);
}

void playSound(int id, int channel) 
{
    Mix_PlayChannel(channel, sounds[id], 0);
}
*/

Mix_Music* loadMusic(std::string filename) {
    // Get the base path
    std::string base_path = std::string(SDL_GetBasePath());

    Mix_Music* music = Mix_LoadMUS( (base_path + filename).c_str());

    return music;
}

void initSounds(void)
{
    // Khởi tạo SDL và SDL_mixer
    if (SDL_Init(SDL_INIT_AUDIO) < 0)
    {
        printf("Lỗi khi khởi tạo SDL: %s\n", SDL_GetError());
        // Xử lý lỗi tại đây 
        exit(0);
    }

    // Khởi tạo âm thanh
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
    {
        printf("Lỗi khi khởi tạo âm thanh: %s\n", Mix_GetError());
        // Xử lý lỗi tại đây 
        exit(0);
    }

    // Tải nhạc nền

    Mix_Music* backgroundMusic = loadMusic("data\\audio\\music.ogg");
    if (backgroundMusic == NULL)
    {
        printf("Lỗi khi tải nhạc nền: %s\n", Mix_GetError());
        // Xử lý lỗi tại đây 
        exit(0);
    }

    // Phát nhạc nền (lặp lại)
    Mix_PlayMusic(backgroundMusic, -1);
}
