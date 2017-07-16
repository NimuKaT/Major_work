/*
 * GameMenu.cpp
 *
 *  Created on: 2017/02/22
 *      Author: Imukat
 */

#include "../Header/GameMenu.h"

GameMenu::GameMenu(SDL_Renderer* renderer_ptr, std::shared_ptr<Input_event> &input_ptr) {
	is_paused = false;
	input_data_ = input_ptr;
	renderer_ptr_ = renderer_ptr;
	game_instance = Engine();
	game_instance.get_data(renderer_ptr_);
	game_instance.load_stage(STAGE_TEST);
}

void GameMenu::update_logic(){
	if (!input_data_.expired()){
		if (input_data_.lock()->key_pressed[KEY_PRESS_ESC]){
			if (!is_paused){
				is_paused = true;

			}
			else{
				is_paused = false;

			}
		}

		if (!is_paused){
			if(!input_data_.expired()){
				game_instance.main_loop(input_data_);
			}
		}
	}
}


void GameMenu::render_texture(){
	std::shared_ptr<Texture> current_game_frame;
	current_game_frame = game_instance.get_last_texture();
	current_game_frame->render(0,0);
	if (!is_paused){

	}
}
