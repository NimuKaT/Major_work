/*
 * Debugger.cpp
 *
 *  Created on: 2017/05/05
 *      Author: Imukat
 */

#include "../Header/Debugger.h"

void Debugger::init(SDL_Renderer* renderer_ptr){
	debug_log.init( renderer_ptr);

	fps_text = "";

	SDL_Rect fps_box;
	fps_box.w = 64;
	fps_box.h = 16;
	frame_rate.init( renderer_ptr, "Sans", fps_text, fps_box);
	frame_rate.set_color( 255, 255, 255, 150);
	frame_rate.set_font_size(32);
	fps_timer.start();
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

	printf(" called");
	if( fps_timer.is_passed(1000) ){
		fps_timer.reset();
		fps_text = std::string( "fps: i");
		frame_rate.set_text( fps_text );

	}
	else{
		frame_count++;
	}

	if( options[FRAME_RATE] ){
		frame_rate.render( 0, 0 );
	}

}
