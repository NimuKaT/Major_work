/*
 * GameMenu.cpp
 *
 *  Created on: 2017/02/22
 *      Author: Imukat
 */

#include "../Header/GameMenu.h"

GameMenu::GameMenu(SDL_Renderer* renderer_ptr, Input_event* input_ptr) {
	is_paused = false;
}


void GameMenu::render_texture(){

}

void GameMenu::update_logic(){
	if ( !is_paused ){
		update_player();
		update_enemy();
	}
	else{

	}
}

void GameMenu::update_player(){
	int x = 0;
	int y = 0;
	if (input_data_->key_pressed[MOVE_UP] == input_data_->key_pressed[MOVE_DOWN]){

	}
	else if (input_data_->key_pressed[MOVE_UP]){
		x = -1;
	}
	else if (input_data_->key_pressed[MOVE_DOWN]){
		x = 1;
	}

	if (input_data_->key_pressed[MOVE_LEFT] == input_data_->key_pressed[MOVE_RIGHT]){

	}
	else if (input_data_->key_pressed[MOVE_LEFT]){
		y = -1;
	}
	else if (input_data_->key_pressed[MOVE_RIGHT]){
		y = 1;
	}
	player.get_movement(x, y);
}

void GameMenu::update_enemy(){

}

void GameMenu::update_stage(){

}

coord GameMenu::check_collision(){
	return coord();
}

void GameMenu::pause_menu(){

}
