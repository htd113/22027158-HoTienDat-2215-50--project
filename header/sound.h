#ifndef SOUND_H
#define SOUND_H

#include <bits/stdc++.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "SDL2/SDL_ttf.h"
#include "defs.h"

Mix_Music* LoadMusic(std::string filename);

/*Chuyển nhạc nền*/
static void musicFinishedCallback(void);

/*Tìm nhạc theo đường dẫn*/
Mix_Chunk* loadMusic(std::string filename);

void load_music_title(const char *file);

/*Tải nhạc nền*/
void load_music_background(void);

/*Tải hiệu ứng âm thanh*/
void loadSounds(void);

void initSounds(void);

/*Phát nhạc nền*/
void playMusic(int loop);

/*Phát âm thanh theo kênh*/
void playSound(int id, int channel);
#endif