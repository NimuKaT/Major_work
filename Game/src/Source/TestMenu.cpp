/*
 * TestMenu.cpp
 *
 *  Created on: 12Jun.,2017
 *      Author: ImuKaT
 */

#include "../Header/TestMenu.h"

#define MIN_FACTOR 1.0f
#define MAX_FACTOR 1024.0f

Test_Menu::Test_Menu( SDL_Renderer* target_renderer, Input_event* input_ptr){
	 _renderer= target_renderer;
	_input_data = input_ptr;

	for( auto &key : key_pressed){
		key = false;
	}

	std::vector<SDL_Rect> clips;
	add_rect_to_vector(clips, 0, 0, 100, 100);
	add_rect_to_vector(clips, 0, 100, 100, 100);
	add_rect_to_vector(clips, 100, 0, 100, 100);
	add_rect_to_vector(clips, 100, 100, 100, 100);
	add_rect_to_vector(clips, 0, 0, 150, 650);

	_texture_balls.set_renderer( _renderer);
	_texture_balls.set_image_path("Assets\\Images\\test_balls.png");
	_texture_balls.set_sprite_rects(clips);
	x = 0;
	y = 0;
}

void Test_Menu::update_logic(){

	if(_input_data->key_pressed[KEY_PRESS_W]){
		y -= 5;

	}
	if(_input_data->key_pressed[KEY_PRESS_A]){
		x -= 5;

	}
	if(_input_data->key_pressed[KEY_PRESS_S]){
		y += 5;

	}
	if(_input_data->key_pressed[KEY_PRESS_D]){
		x += 5;

	}
	if(_input_data->key_pressed[KEY_PRESS_UP]){
		if ( scale_factor < MAX_FACTOR ){
			scale_factor += 1;
		}
	}
	if(_input_data->key_pressed[KEY_PRESS_DOWN]){
		if ( scale_factor > MIN_FACTOR ){
			scale_factor -= 1;
		}
	}
}

void Test_Menu::render_Texture(){
//	_texture_balls.set_scale( scale_factor );
//	SDL_RenderSetLogicalSize( _renderer_ptr, 16 * scale_factor, 9 * scale_factor);
//	SDL_RenderSetScale( _renderer_ptr, scale_factor, scale_factor );

//	_texture_balls.set_texture_alpha(texture_opacity);
	_texture_balls.render( x, y, 1 );
}
