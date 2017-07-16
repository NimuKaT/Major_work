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
	Timer fps_timer_;
	bool options_[OPTIONS_LENGTH];
	Uint8 frame_count_ = 0;
	int menu_ID_ = 0;

	Texture debug_log_;
	Text frame_rate_;
	Text mouse_location_;
	Text current_menu_;

	std::string fps_text_;
	std::string mouse_text_;
	std::string menu_name_;

	std::weak_ptr<Input_event> input_data_;

public:
	void init(SDL_Renderer*, std::shared_ptr<Input_event> &input_ptr);
	void change_option(std::string, bool);
	void render();

};

#endif /* DEBUGGER_H_ */
