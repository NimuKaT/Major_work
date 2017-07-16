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
#include <memory>
#include <forward_list>
#include <tuple>
#include <array>

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>

#if defined(WIN32) || defined(_WIN32) || defined(__WIN32) && !defined(__CYGWIN__)
static const std::string slash="\\";
#else
static const std::string slash="/";
#endif

#define PI 3.14159265

//Screen dimension constants
extern int SCREEN_WIDTH;
extern int SCREEN_HEIGHT;
extern Uint8 INIT_MENU;
const Uint32 TEMP_FRAME_RATE_CAP = 60;
const Uint32 TEMP_TICK_PER_FRAME = 1000 / TEMP_FRAME_RATE_CAP;

enum TEXTURE_ID{
	PLAYER,
	TEMP_MAIN_MENU_BACKGROUND,
	TEST_BALL,
	TEST_UI_ELEMENT,
	TEST,
	DEFAULT_TEXTURE_ID
};

extern std::vector<std::string> IMAGE_PATHS;
extern std::vector<std::vector<SDL_Rect>> IMAGE_RECTS;


enum KEY_PRESS {
	KEY_PRESS_W,
	KEY_PRESS_A,
	KEY_PRESS_S,
	KEY_PRESS_D,
	KEY_PRESS_UP,
	KEY_PRESS_LEFT,
	KEY_PRESS_DOWN,
	KEY_PRESS_RIGHT,
	KEY_PRESS_ESC,
	KEY_PRESS_MB_1,
	KEY_PRESS_DEFAULT

};

enum MENU_ID{
	MAIN_MENU,
	OPTIONS_MENU,
	STAGE_SELECT_MENU,
	GAME_MENU,
	TEST_MENU,
	DEFAULT_MENU
};

struct Input_event{
	std::array<bool, KEY_PRESS_DEFAULT> key_pressed;
	int mouse_x;
	int mouse_y;
};

enum STAGE_ID{
	STAGE_TEST,
	STAGE_TUTORIAL,
	STAGE_1_1,
	STAGE_DEFAULT
};

enum ENEMY_TYPE_IF{
	TEST_BOT,
	DEAFAULT_ENEMY
};

enum TEST_BALL_RECT{
	BALL_RED,
	BALL_GREEN,
	BALL_BLUE,
	BALL_YELLOW,
	BALL_LENGTH
};

//TODO remove basic arrays and pointers

#endif /* GLOBAL_H_ */
