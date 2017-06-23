/*
 * Debugger.h
 *
 *  Created on: 2017/05/05
 *      Author: Imukat
 */

#ifndef DEBUGGER_H_
#define DEBUGGER_H_

#include <String>

#include "Timer.h"
#include "Texture.h"
#include "Text.h"

enum DEBUGGER_OPTIONS{
	FRAME_RATE,
	MOUSE_LOCATION,
	CURRENT_MENU,
	OPTIONS_LENGTH
};

class Debugger {
private:
	Timer fps_timer;
	bool options[OPTIONS_LENGTH];
	Uint8 frame_count;
	int mouse_x, mouse_y;
	int menu_ID;


	Texture debug_log;
	Text frame_rate;
	Text mouse_location;
	Text current_menu;

	std::string fps_text;
	std::string mouse_text;
	std::string menu_name;

public:
	void init( SDL_Renderer* );
	void change_option( std::string, bool );
	void render();
	void getMousePos( std::tuple<int,int> );

};

#endif /* DEBUGGER_H_ */
