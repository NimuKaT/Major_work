/*
 * Menu.cpp
 *
 *  Created on: 14Jan.,2017
 *      Author: ImuKaT
 */

#include "../Header/Menu.h"

//inline MenuManager::~MenuManager(){};

void create_queue(std::vector<render_queue>* queue, int sprite_number, int x_coordinate, int y_coordinate, int clip_number){
	render_queue new_queue = {sprite_number, x_coordinate, y_coordinate, clip_number};
	queue->push_back(new_queue);
}
int MenuManager::change_menu(){
	int change_menu = next_menu;
	next_menu = current_menu;
	return change_menu;
}

bool MenuManager::quit_game(){
	return quit;
}


//TODO Memory allocator, deallocator and deconstructor
MainMenu::MainMenu(SDL_Renderer* renderer_ptr, std::shared_ptr<Input_event> &input_ptr){
	current_menu = MAIN_MENU;
	next_menu = current_menu;

	renderer_ptr_ = renderer_ptr;
	input_data_ = input_ptr;
	quit = false;

	game_logo = Text();
	game_logo.set_renderer(renderer_ptr_);
	game_logo.set_text("Gun Mayhem");
	game_logo.set_font("Sans");
	game_logo.set_font_size(0xFF);
	game_logo.set_color(0xFF, 0x36, 0x80, 0xFF);

	element_deco.set_renderer(renderer_ptr_);
	element_deco.set_image_path(IMAGE_PATHS[TEST_UI_ELEMENT]);
	element_deco.set_sprite_rects(IMAGE_RECTS[TEST_UI_ELEMENT]);

	play_button_.init_element(renderer_ptr_, "Play", &element_deco, 0);
	play_button_.hide_element(false);
	play_button_.set_position(1595,1020);

	options_button_.init_element(renderer_ptr_, "Options", &element_deco, 0);
	options_button_.hide_element(false);
	options_button_.set_position(1595,1270);

	exit_button_.init_element(renderer_ptr_, "exit", &element_deco, 0);
	exit_button_.hide_element(false);
	exit_button_.set_position(1595,1520);

	spritePaths.push_back(IMAGE_PATHS[TEST_BALL]);
	spritePaths.push_back(IMAGE_PATHS[TEST_UI_ELEMENT]);
	main_menu_background.set_renderer(renderer_ptr_);
	main_menu_background.set_image_path(IMAGE_PATHS[TEMP_MAIN_MENU_BACKGROUND]);

}

void MainMenu::render_texture(){
	main_menu_background.render(0,0);
	play_button_.draw_element();
	options_button_.draw_element();
	exit_button_.draw_element();
	game_logo.render(1920-game_logo.get_size().x/2 ,400);
}

void MainMenu::update_logic(){
	if (!input_data_.expired()){
		if (input_data_.lock()->key_pressed[KEY_PRESS_W]){
		}
		if (input_data_.lock()->key_pressed[KEY_PRESS_A]){
		}
		if (input_data_.lock()->key_pressed[KEY_PRESS_S]){
		}
		if (input_data_.lock()->key_pressed[KEY_PRESS_D]){
		}
		if (input_data_.lock()->key_pressed[KEY_PRESS_DEFAULT]){
		}
		play_button_.update_element(input_data_.lock()->mouse_x, input_data_.lock()->mouse_y, input_data_.lock()->key_pressed[KEY_PRESS_MB_1]);
		options_button_.update_element(input_data_.lock()->mouse_x, input_data_.lock()->mouse_y, input_data_.lock()->key_pressed[KEY_PRESS_MB_1]);
		exit_button_.update_element(input_data_.lock()->mouse_x, input_data_.lock()->mouse_y, input_data_.lock()->key_pressed[KEY_PRESS_MB_1]);
	}
	if (play_button_.element_clicked()){
		next_menu = GAME_MENU;
	}
	if (exit_button_.element_clicked()){
		quit = true;
	}
}

