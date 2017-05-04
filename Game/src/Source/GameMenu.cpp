/*
 * GameMenu.cpp
 *
 *  Created on: 2017/02/22
 *      Author: Imukat
 */

#include "../Header/GameMenu.h"

GameMenu::GameMenu( SDL_Renderer* main_renderer ) {
	is_paused = false;
}

GameMenu::~GameMenu(){

}

void GameMenu::render_Texture(){

}

void GameMenu::event_Handler( SDL_Event& event, bool& quit ){
	while( SDL_PollEvent( &event ) != 0 ){
		if(event.type == SDL_QUIT){
				quit = true;
				break;
		}
		else if( event.type == SDL_KEYDOWN){
			switch( event.key.keysym.sym ){
				case SDLK_w:{
	//				std::cout << "w down" << std::endl;
					key_pressed[KEY_PRESS_W] = true;
					break;
				}
				case SDLK_a:{
	//				std::cout << "a down" << std::endl;
					key_pressed[KEY_PRESS_A] = true;
					break;
				}
				case SDLK_s:{
	//				std::cout << "s down" << std::endl;
					key_pressed[KEY_PRESS_S] = true;
					break;
				}
				case SDLK_d:{
	//				std::cout << "d down" << std::endl;
					key_pressed[KEY_PRESS_D] = true;
					break;
				}
			};
		}
		else if( event.type == SDL_KEYUP){
			switch( event.key.keysym.sym ){
				case SDLK_w:{
	//				std::cout << "w up" << std::endl;
					key_pressed[KEY_PRESS_W] = false;
					break;
				}
				case SDLK_a:{
	//				std::cout << "a up" << std::endl;
					key_pressed[KEY_PRESS_A] = false;
					break;
				}
				case SDLK_s:{
	//				std::cout << "s up" << std::endl;
					key_pressed[KEY_PRESS_S] = false;
					break;
				}
				case SDLK_d:{
	//				std::cout << "d up" << std::endl;
					key_pressed[KEY_PRESS_D] = false;
					break;
				}
			}
		}

		else if( event.type == SDL_MOUSEBUTTONUP ){
			if( event.button.button == SDL_BUTTON_LEFT ){

			}
		}
		else if( event.type == SDL_MOUSEBUTTONDOWN ){
			if( event.button.button == SDL_BUTTON_LEFT ){

			}
		}
		else if (event.type == SDL_MOUSEMOTION ){
		SDL_GetMouseState( &_mouse_x, &_mouse_y );
//		std::cout << _mouse_x << " " << _mouse_y << std::endl;	logPoint
		}

	}
}

void GameMenu::update_logic(){
	if ( !is_paused ){
		update_player();
		update_enemy();
		//
	}
	else{

	}
}

void GameMenu::update_player(){
	int x, y = 0;

	if( key_pressed[MOVE_UP] == key_pressed[MOVE_DOWN] ){

	}
	else if( key_pressed[MOVE_UP] ){
		x = -1;
	}
	else if( key_pressed[MOVE_DOWN] ){
		x = 1;
	}

	if( key_pressed[MOVE_LEFT] == key_pressed[MOVE_RIGHT] ){

	}
	else if( key_pressed[MOVE_LEFT] ){
		y = -1;
	}
	else if( key_pressed[MOVE_RIGHT] ){
		y = 1;
	}

	player.get_movement( x, y );

}

void GameMenu::update_enemy(){

}

void GameMenu::update_stage(){

}

coord GameMenu::check_collision(){

}

void GameMenu::pause_menu(){

}
