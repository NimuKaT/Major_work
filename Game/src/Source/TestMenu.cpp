/*
 * TestMenu.cpp
 *
 *  Created on: 12Jun.,2017
 *      Author: ImuKaT
 */

#include "../Header/TestMenu.h"

Test_Menu::Test_Menu(SDL_Renderer* target_renderer, std::shared_ptr<Input_event> &input_ptr){
	next_menu = TEST_MENU;
	renderer_ptr_ = target_renderer;
	input_data_ = input_ptr;
	button_event_ = false;

//	Testing basic texture/spriteSheet manipulation
	texture_balls_.set_renderer(renderer_ptr_);
	texture_balls_.set_image_path(IMAGE_PATHS[TEST_BALL]);
	texture_balls_.set_sprite_rects(IMAGE_RECTS[TEST_BALL]);
	x_ = 0;
	y_ = 0;

//	Testing UI_eleemnt functions
	decoration_sprite_.set_renderer(renderer_ptr_);
	decoration_sprite_.set_image_path(IMAGE_PATHS[TEST_UI_ELEMENT]);	//("Assets"+slash+"Images"+slash+"test_UI_element.png");
	decoration_sprite_.set_sprite_rects(IMAGE_RECTS[TEST_UI_ELEMENT]);
	test_button_.init_element(renderer_ptr_, "testing button", &decoration_sprite_, 0);
	test_button_.set_position(400, 400);
	test_button_.set_listner(input_data_.lock().get()); // Dodge fix later
	test_button_.set_event_trigger(&button_event_);

}

void Test_Menu::update_logic(){
	if (!input_data_.expired()){
		if (input_data_.lock()->key_pressed[KEY_PRESS_W]){
			y_ -= 5;
		}
		if (input_data_.lock()->key_pressed[KEY_PRESS_A]){
			x_ -= 5;
		}
		if (input_data_.lock()->key_pressed[KEY_PRESS_S]){
			y_ += 5;
		}
		if (input_data_.lock()->key_pressed[KEY_PRESS_D]){
			x_ += 5;
		}
	}
	test_button_.update_event();
}

void Test_Menu::render_texture(){
//	_texture_balls.set_texture_alpha(texture_opacity);
	texture_balls_.render(x_, y_, BALL_GREEN);
	test_button_.draw_element();
	if (button_event_){
		texture_balls_.render(0, 0, BALL_RED);
	}

}
