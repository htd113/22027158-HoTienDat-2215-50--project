#ifndef STAGE_H
#define STAGE_H

#include <bits/stdc++.h>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"
#include "SDL2/SDL_mixer.h"
#include "structs.h"
#include "defs.h"
#include "draw.h"
#include "init.h"
#include "input.h"
#include "util.h"
#include "sound.h"

void initStage(void);
void capFrameRate(long *then, float *remainder);

#endif
