/*
 * TestMenu.cpp
 *
 *  Created on: 12Jun.,2017
 *      Author: ImuKaT
 */

#include "../Header/TestMenu.h"

Test_Menu::Test_Menu(SDL_Renderer* target_renderer, Input_event* input_ptr){
	renderer_ptr_ = target_renderer;
	input_data_ = input_ptr;
	button_event_ = false;

//	Testing basic texture/spriteSheet manipulation
	std::vector<SDL_Rect> clips;
	add_rect_to_vector(clips, 0, 0, 100, 100);
	add_rect_to_vector(clips, 0, 100, 100, 100);
	add_rect_to_vector(clips, 100, 0, 100, 100);
	add_rect_to_vector(clips, 100, 100, 100, 100);
	add_rect_to_vector(clips, 0, 0, 150, 650);
	texture_balls_.set_renderer( renderer_ptr_);
	texture_balls_.set_image_path("Assets\\Images\\test_balls.png");
	texture_balls_.set_sprite_rects(clips);
	x_ = 0;
	y_ = 0;

//	Testing UI_eleemnt functions
	std::vector<SDL_Rect> decoration_rect;
	add_rect_to_vector(decoration_rect, 0, 0, 150, 650);
	decoration_sprite_.set_renderer(renderer_ptr_);
	decoration_sprite_.set_image_path("Assets"+slash+"Images"+slash+"test_UI_element.png");
	decoration_sprite_.set_sprite_rects(decoration_rect);
	test_button_.init_element(renderer_ptr_, "testing button", &decoration_sprite_, 0);
	test_button_.set_position(400, 400);
	test_button_.set_listner(input_data_);
	test_button_.set_event_trigger(&button_event_);

}

void Test_Menu::update_logic(){
	if (input_data_->key_pressed[KEY_PRESS_W]){
		y_ -= 5;
	}
	if (input_data_->key_pressed[KEY_PRESS_A]){
		x_ -= 5;
	}
	if (input_data_->key_pressed[KEY_PRESS_S]){
		y_ += 5;
	}
	if (input_data_->key_pressed[KEY_PRESS_D]){
		x_ += 5;
	}
	test_button_.update_event();
}

void Test_Menu::render_texture(){
//	_texture_balls.set_texture_alpha(texture_opacity);
	texture_balls_.render(x_, y_, 1);
	test_button_.draw_element();
	if (button_event_){
		texture_balls_.render(0, 0, 1);
	}

}
