#include "sound.h"

/*Danh sách tên tệp nhạc*/
std::vector<std::string> musicList = { "data\\audio\\music01.mp3",
                                        "data\\audio\\music02.mp3",
                                        "data\\audio\\music00.mp3"
                                        }; 
int currentTrackIndex = 0; // Chỉ số của bài hát hiện tại
Mix_Music* backgroundMusic = NULL; // Biến toàn cục để theo dõi nhạc nền hiện tại
Mix_Music* LoadMusic(std::string filename) 
{
    // Get the base path
    std::string base_path = std::string(SDL_GetBasePath());

    Mix_Music* music = Mix_LoadMUS( (base_path + filename).c_str());

    return music;
}

/*Chuyển nhạc nền*/
static void musicFinishedCallback(void) 
{
    // Xử lý sự kiện khi nhạc nền kết thúc
    // Chuyển sang bài hát khác ở đây (tải và phát bài hát tiếp theo)
    // Ví dụ:
    currentTrackIndex = (currentTrackIndex + 1) % musicList.size();
    Mix_FreeMusic(backgroundMusic);
    backgroundMusic = LoadMusic(musicList[currentTrackIndex]);
    Mix_PlayMusic(backgroundMusic, 1);
}

Mix_Chunk* sounds[MAX_SND_CHANNELS];
Mix_Music* music = NULL;

/*Tìm nhạc theo đường dẫn*/
Mix_Chunk* loadMusic(std::string filename) 
{
    // Get the base path
    std::string base_path = std::string(SDL_GetBasePath());

    Mix_Chunk* music = Mix_LoadWAV( (base_path + filename).c_str());

    return music;
}

/*Tải nhạc nền*/
void load_music_background(void) 
{
     
    backgroundMusic = LoadMusic(musicList[currentTrackIndex]);
    if (backgroundMusic == NULL)
    {
        printf("Lỗi khi tải nhạc nền: %s\n", Mix_GetError());
        // Xử lý lỗi tại đây 
        exit(0);
    }

    // Phát nhạc nền
    Mix_PlayMusic(backgroundMusic, 1);

    // Đăng ký callback khi nhạc nền kết thúc
    Mix_HookMusicFinished(musicFinishedCallback);
}

/*Tải hiệu ứng âm thanh*/
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

    load_music_background();
}

/*Phát nhạc nền*/
void playMusic(int loop) 
{
    Mix_PlayMusic(music, (loop) ? -1 : 0);
}

/*Phát âm thanh theo kênh*/
void playSound(int id, int channel) 
{
    Mix_PlayChannel(channel, sounds[id], 0);
}
