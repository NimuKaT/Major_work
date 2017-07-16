/*
 * Debugger.cpp
 *
 *  Created on: 2017/05/05
 *      Author: Imukat
 */

#include "../Header/Debugger.h"

void Debugger::init(SDL_Renderer* renderer_ptr, std::shared_ptr<Input_event> &input_ptr){
//	main debug log texture
	debug_log_.set_renderer(renderer_ptr);

	input_data_ = input_ptr;

//	fps texture
	fps_text_ = "fps: 0";
	SDL_Rect fps_box {0,0,150,60};
	frame_rate_.init(renderer_ptr, "Sans", fps_text_, fps_box);
	frame_rate_.set_color(0, 0, 0, 150);
	frame_rate_.set_font_size(40);

//	Mouse position texture
	mouse_text_ = "x: 	y: ";
	SDL_Rect mouse_box {0, 0, 320, 60};
	mouse_location_.init(renderer_ptr, "Sans", mouse_text_, mouse_box);
	mouse_location_.set_color(0, 0, 0, 255);
	mouse_location_.set_font_size(40);

//	Intitialise fps timer
	fps_timer_.start();

}

void Debugger::change_option(std::string option_name, bool state){
	if (option_name == "frame_rate"){
		options_[FRAME_RATE] = state;
	}
	else if (option_name == "mouse_location"){
		options_[MOUSE_LOCATION] = state;
	}
	else if (option_name == "current_menu"){
		options_[CURRENT_MENU] = state;
	}
}

void Debugger::render(){
	if (fps_timer_.is_passed(1000)){
		fps_timer_.reset();
		fps_text_ = "fps: " + std::to_string(frame_count_);
		frame_rate_.set_text(fps_text_);
		frame_count_ = 0;
	}
	if (options_[FRAME_RATE]){
//		printf(fps_text.c_str());
		frame_rate_.render(0, 0);
		frame_count_++;
	}
	if (options_[MOUSE_LOCATION]){
		if(!input_data_.expired()){
			mouse_text_ = "x: " + std::to_string(input_data_.lock()->mouse_x) + " y: " + std::to_string(input_data_.lock()->mouse_y);
		}
		mouse_location_.set_text(mouse_text_);
		mouse_location_.render(0, 60);
	}
}
