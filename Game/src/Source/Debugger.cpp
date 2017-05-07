/*
 * Debugger.cpp
 *
 *  Created on: 2017/05/05
 *      Author: Imukat
 */

#include "../Header/Debugger.h"

void Debugger::init(SDL_Renderer* renderer_ptr){
	debug_log.init( renderer_ptr);

	SDL_Rect fps_box;
	fps_box.w = 64;
	fps_box.h = 16;
	frame_rate.init( renderer_ptr, "Sans", fps_text, fps_box);
}

void Debugger::change_option( std::string option_name, bool state ){

	if ( option_name == "frame_rate" ){
		options[FRAME_RATE] = state;
	}

	else if ( option_name == "mouse_location" ){
		options[MOUSE_LOCATION] = state;
	}

	else if ( option_name == "current_menu" ){
		options[CURRENT_MENU] = state;
	}
}

void Debugger::render(){

}
