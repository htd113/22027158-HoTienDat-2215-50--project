#ifndef SOUND_H
#define SOUND_H

#include "init.h"

/*void loadMusic(char *filename);

void initSounds(void) ;

//static void loadSounds(void);

void playMusic(int loop);

void playSound(int id, int channel);*/

Mix_Music* loadMusic(std::string filename);
void initSounds(void);

#endif