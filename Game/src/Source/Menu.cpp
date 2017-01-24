/*
 * Menu.cpp
 *
 *  Created on: 14Jan.,2017
 *      Author: ImuKaT
 */

#include "../Header/Menu.h"

inline MenuManager::~MenuManager(){};



MainMenu::MainMenu(SDL_Renderer* targetRenderer){

	_renderer = targetRenderer;
	spritePaths.push_back("Assets/Images/test_balls.png");

	std::string path_bg = "Assets/Images/temp_main_menu_background.png";
	main_menu_background.init(targetRenderer, path_bg);
	std::vector< SDL_Rect > clips ;
	add_rect_to_vector(clips, 0, 0, 100, 100);
	add_rect_to_vector(clips, 0, 100, 100, 100);
	add_rect_to_vector(clips, 100, 0, 100, 100);
	add_rect_to_vector(clips, 100, 100, 100, 100);

//	spritePaths.push_back("Assets/Images/player.png");

	std::string paths;

	for( int i = 0; i < spritePaths.size(); i++){
		Texture temp_texture;
		temp_texture.init( targetRenderer, spritePaths[i], clips);
		sprite_sheets.push_back(temp_texture);
	}

	for( int i = 0; i < KEY_PRESS_DEFAULT; i++){
		key_pressed[i] = false;
	}


};

void MainMenu::renderTexture(){

	main_menu_background.render();
	for( auto &current_queue : queue){
		sprite_sheets[current_queue[0]].render(current_queue[1]);
	}

	queue.clear();

};

void MainMenu::eventHandler( SDL_Event &event, bool &quit ){
	while( SDL_PollEvent( &event ) != 0 ){
		if(event.type == SDL_QUIT){
				quit = true;
				break;
		}
		else if( event.type == SDL_KEYDOWN){
			switch( event.key.keysym.sym ){
				case SDLK_w:{
//					std::cout << "w down" << std::endl;
					key_pressed[KEY_PRESS_W] = true;
					break;
				}
				case SDLK_a:{
//					std::cout << "a down" << std::endl;
					key_pressed[KEY_PRESS_A] = true;
					break;
				}
				case SDLK_s:{
//					std::cout << "s down" << std::endl;
					key_pressed[KEY_PRESS_S] = true;
					break;
				}
				case SDLK_d:{
//					std::cout << "d down" << std::endl;
					key_pressed[KEY_PRESS_D] = true;
					break;
				}
			};
		}
		else if( event.type == SDL_KEYUP){
			switch( event.key.keysym.sym ){
				case SDLK_w:{
//					std::cout << "w up" << std::endl;
					key_pressed[KEY_PRESS_W] = false;
					break;
				}
				case SDLK_a:{
//					std::cout << "a up" << std::endl;
					key_pressed[KEY_PRESS_A] = false;
					break;
				}
				case SDLK_s:{
//					std::cout << "s up" << std::endl;
					key_pressed[KEY_PRESS_S] = false;
					break;
				}
				case SDLK_d:{
//					std::cout << "d up" << std::endl;
					key_pressed[KEY_PRESS_D] = false;
					break;
				}
			}

		}
	}

	if(key_pressed[KEY_PRESS_W]){

		std::vector<int> new_queue;
		new_queue.push_back( 0 );
		new_queue.push_back( 0 );
		queue.push_back(new_queue);
	}
	if(key_pressed[KEY_PRESS_A]){

		std::vector<int> new_queue;
		new_queue.push_back( 0 );
		new_queue.push_back( 1 );
		queue.push_back(new_queue);
	}
	if(key_pressed[KEY_PRESS_S]){

		std::vector<int> new_queue;
		new_queue.push_back( 0 );
		new_queue.push_back( 2 );
		queue.push_back(new_queue);
	}
	if(key_pressed[KEY_PRESS_D]){

		std::vector<int> new_queue;
		new_queue.push_back( 0 );
		new_queue.push_back( 3 );
		queue.push_back(new_queue);
	}
	if(key_pressed[KEY_PRESS_DEFAULT]){

	}



};

