/*
 * Menu.cpp
 *
 *  Created on: 14Jan.,2017
 *      Author: ImuKaT
 */

#include "../Header/Menu.h"

//inline MenuManager::~MenuManager(){};

void MenuManager::event_Handler( SDL_Event &event, bool &quit ){
	int keyState = -1;
	while( SDL_PollEvent( &event ) != 0 ){
		if(event.type == SDL_QUIT){
				quit = true;
				break;
		}
		else if( event.type == SDL_KEYDOWN){
			keyState = 1;
		}
		else if( event.type == SDL_KEYUP){
			keyState = 0;
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
			_mouse_x = event.button.x;
			_mouse_y = event.button.y;
//			SDL_GetMouseState( &_mouse_x, &_mouse_y );
//			std::cout << _mouse_x << " " << _mouse_y << std::endl;	//logPoint

		}

		if( keyState != -1){
			switch( event.key.keysym.sym ){
				case SDLK_w:{
					key_pressed[KEY_PRESS_W] = keyState;
					break;
				}
				case SDLK_a:{
					key_pressed[KEY_PRESS_A] = keyState;
					break;
				}
				case SDLK_s:{
					key_pressed[KEY_PRESS_S] = keyState;
					break;
				}
				case SDLK_d:{
					key_pressed[KEY_PRESS_D] = keyState;
					break;
				}
				case SDLK_UP:{
					key_pressed[KEY_PRESS_UP] = keyState;
					break;
				}
				case SDLK_LEFT:{
					key_pressed[KEY_PRESS_LEFT] = keyState;
					break;
				}
				case SDLK_DOWN:{
					key_pressed[KEY_PRESS_DOWN] = keyState;
					break;
				}
				case SDLK_RIGHT:{
					key_pressed[KEY_PRESS_RIGHT] = keyState;
					break;
				}
			};
			keyState = -1;
		}
	}
	update_logic();
};

std::tuple<int,int> MenuManager::returnMousePos(){
	auto mousePos = std::make_tuple( _mouse_x, _mouse_y );

	return mousePos;
}

void create_queue( std::vector< render_queue >* queue, int sprite_number, int x_coordinate, int y_coordinate, int clip_number ){
	render_queue new_queue = {sprite_number, x_coordinate, y_coordinate, clip_number};
	queue->push_back(new_queue);
}
//TODO Memory allocator, deallocator and deconstructor
MainMenu::MainMenu(SDL_Renderer* targetRenderer){

	_renderer = targetRenderer;
	spritePaths.push_back("Assets/Images/test_balls.png");
	spritePaths.push_back("Assets/Images/test_UI_element.png");

	for( auto &key : key_pressed){
		key = false;
	}

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

	for( Uint8 i = 0; i < spritePaths.size(); i++){
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

void MainMenu::render_Texture(){

	main_menu_background.render();
	for( auto &current_queue : queue){
		sprite_sheets[current_queue.sprite_num].render(current_queue.x, current_queue.y, current_queue.clip_num);
	}

	test_text.render( 300, 300 );

	_test_button.draw_element();

	queue.clear();

};


void MainMenu::update_logic(){

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
}

