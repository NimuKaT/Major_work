/*
 * Menu.cpp
 *
 *  Created on: 14Jan.,2017
 *      Author: ImuKaT
 */

#include "../Header/Menu.h"

inline MenuManager::~MenuManager(){};

void create_queue( std::vector< std::vector< int > >* queue, int spire_number, int x_coordinate, int y_coordinate, int clip_number ){
	std::vector< int > new_queue;
	new_queue.push_back(spire_number);
	new_queue.push_back(x_coordinate);
	new_queue.push_back(y_coordinate);
	new_queue.push_back(clip_number);
	queue->push_back(new_queue);
}

MainMenu::MainMenu(SDL_Renderer* targetRenderer){

	_renderer = targetRenderer;
	spritePaths.push_back("Assets/Images/test_balls.png");
	spritePaths.push_back("Assets/Images/test_UI_element.png");


	std::string path_bg = "Assets/Images/temp_main_menu_background.png";
	main_menu_background.init(targetRenderer, path_bg);
	std::vector< SDL_Rect > clips ;
	add_rect_to_vector(clips, 0, 0, 100, 100);
	add_rect_to_vector(clips, 0, 100, 100, 100);
	add_rect_to_vector(clips, 100, 0, 100, 100);
	add_rect_to_vector(clips, 100, 100, 100, 100);
	add_rect_to_vector(clips, 0, 0, 150, 650);

	SDL_Rect test_text_clip = {0, 0, 300, 200};
	test_text.init(_renderer, "Sans", "Hello, World!", test_text_clip);

	test_text.set_color( 0, 0, 0, 100 );
	test_text.set_font_size(16);

//	spritePaths.push_back("Assets/Images/player.png");



	std::string paths;

	for( int i = 0; i < spritePaths.size(); i++){
		Texture temp_texture;
		temp_texture.init( targetRenderer, spritePaths[i], clips);
		sprite_sheets.push_back(temp_texture);
	}

	_test_button.init_element( _renderer, "Hello, World!", &sprite_sheets[1], 4 );
	_test_button.set_position(300, 300);

	for( int i = 0; i < KEY_PRESS_DEFAULT; i++){
		key_pressed[i] = false;
	}


};

void MainMenu::renderTexture(){

	main_menu_background.render();
	for( auto &current_queue : queue){
		sprite_sheets[current_queue[0]].render(current_queue[1], current_queue[2], current_queue[3]);
	}

	test_text.render( 300, 300 );

	_test_button.draw_element();

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

		create_queue( &queue, 0, 0, 0, 0 );
	}
	if(key_pressed[KEY_PRESS_A]){

		create_queue( &queue, 0, 0, 0, 1);
	}
	if(key_pressed[KEY_PRESS_S]){

		create_queue( &queue, 0, 0, 0, 2);
	}
	if(key_pressed[KEY_PRESS_D]){

		create_queue( &queue, 0, 0, 0, 3);
	}
	if(key_pressed[KEY_PRESS_DEFAULT]){

	}



};

