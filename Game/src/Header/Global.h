/*
 * Global.h
 *
 *  Created on: 24Jan.,2017
 *      Author: ImuKaT
 */

#ifndef GLOBAL_H_
#define GLOBAL_H_

#include <vector>
#include <string>
#include <iostream>
#include <stdio.h>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

//Screen dimension constants
const int SCREEN_WIDTH = 1366;
const int SCREEN_HEIGHT = 720;
const int TEMP_FRAME_RATE_CAP = 60;
const int TEMP_TICK_PER_FRAME = 1000 / TEMP_FRAME_RATE_CAP;

enum KEY_PRESS {
	KEY_PRESS_W,
	KEY_PRESS_A,
	KEY_PRESS_S,
	KEY_PRESS_D,
	KEY_PRESS_DEFAULT

};

#endif /* GLOBAL_H_ */
