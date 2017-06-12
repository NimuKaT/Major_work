/*
 * TestMenu.cpp
 *
 *  Created on: 12Jun.,2017
 *      Author: ImuKaT
 */

#include "../Header/TestMenu.h"

Test_Menu::Test_Menu( SDL_Renderer* target_renderer){
	_renderer_ptr = target_renderer;
	std::vector<SDL_Rect> clips;
	add_rect_to_vector(clips, 0, 0, 100, 100);
	add_rect_to_vector(clips, 0, 100, 100, 100);
	add_rect_to_vector(clips, 100, 0, 100, 100);
	add_rect_to_vector(clips, 100, 100, 100, 100);
	add_rect_to_vector(clips, 0, 0, 150, 650);

	_texture_balls.init( _renderer_ptr, "Assets/Images/test_balls.png", clips);
}

void Test_Menu::update_logic(){

	if(key_pressed[KEY_PRESS_W]){
		texture_opacity += 1;

	}
	if(key_pressed[KEY_PRESS_A]){


	}
	if(key_pressed[KEY_PRESS_S]){
		texture_opacity -= 1;

	}
	if(key_pressed[KEY_PRESS_D]){


	}
	if(key_pressed[KEY_PRESS_DEFAULT]){


	}

}

void Test_Menu::render_Texture(){
	_texture_balls.set_texture_alpha(texture_opacity);
	_texture_balls.render( 300, 300, 1 );
}
