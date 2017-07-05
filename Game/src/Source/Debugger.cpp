/*
 * Debugger.cpp
 *
 *  Created on: 2017/05/05
 *      Author: Imukat
 */

#include "../Header/Debugger.h"

void Debugger::init(SDL_Renderer* renderer_ptr, Input_event* input_ptr){
//	main debug log texture
	debug_log.init( renderer_ptr);

	input_data = input_ptr;

//	fps texture
	fps_text = "fps: 0";

	SDL_Rect fps_box;
	fps_box.w = 150;
	fps_box.h = 60;
	fps_box.x = 0;
	fps_box.y = 0;

	frame_rate.init( renderer_ptr, "Sans", fps_text, fps_box);
	frame_rate.set_color( 0, 0, 0, 150);
	frame_rate.set_font_size(40);

//	Mouse position texture

	mouse_text = "x: 	y: ";
	SDL_Rect mouse_box {0, 0, 320, 60};
	mouse_location.init( renderer_ptr, "Sans", mouse_text, mouse_box );
	mouse_location.set_color( 0, 0, 0, 255 );
	mouse_location.set_font_size(40);

//	Intitialise fps timer

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


	if( fps_timer.is_passed(1000) ){
		fps_timer.reset();
		fps_text = "fps: " + std::to_string( frame_count );
		frame_rate.set_text( fps_text );
		frame_count = 0;

	}

	if( options[FRAME_RATE] ){
//		printf(fps_text.c_str());
		frame_rate.render( 0, 0 );
		frame_count++;
	}

	if( options[MOUSE_LOCATION] ){
//		SDL_GetMouseState( &mouse_x, &mouse_y );
		mouse_text = "x: " + std::to_string(input_data->mouse_x) + " y: " + std::to_string(input_data->mouse_y);
		mouse_location.set_text( mouse_text );
		mouse_location.render( 0, 60 );

	}

}

void Debugger::getMousePos( std::tuple<int,int> mousePos ){
	mouse_x = std::get<0>(mousePos);
	mouse_y = std::get<1>(mousePos);
}

