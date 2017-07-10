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
//TODO Memory allocator, deallocator and deconstructor
MainMenu::MainMenu(SDL_Renderer* renderer_ptr, Input_event* input_ptr){
	renderer_ptr_ = renderer_ptr;
	input_data_ = input_ptr;
	spritePaths.push_back("Assets\\Images\\test_balls.png");
	spritePaths.push_back("Assets\\Images\\test_UI_element.png");
	std::string path_bg = "Assets\\Images\\temp_main_menu_background.png";
	main_menu_background.set_renderer(renderer_ptr);
	main_menu_background.set_image_path(path_bg);

	std::vector< SDL_Rect > clips ;
	add_rect_to_vector(clips, 0, 0, 100, 100);
	add_rect_to_vector(clips, 0, 100, 100, 100);
	add_rect_to_vector(clips, 100, 0, 100, 100);
	add_rect_to_vector(clips, 100, 100, 100, 100);
	add_rect_to_vector(clips, 0, 0, 150, 650);
	SDL_Rect test_text_clip = {0, 0, 300, 200};

	test_text.init(renderer_ptr_, "Sans", "Hello, World!", test_text_clip);
	test_text.set_color(0, 0, 0, 100);
	test_text.set_font_size(16);

	for (Uint8 i = 0; i < spritePaths.size(); i++){
		SpriteSheet temp_texture;
		temp_texture.set_renderer(renderer_ptr_);
		temp_texture.set_image_path(spritePaths[i]);
		temp_texture.set_sprite_rects(clips);
		sprite_sheets.push_back(temp_texture);
	}
	_test_button.init_element(renderer_ptr_, "Hello, World!", &sprite_sheets[1], 4);
	_test_button.set_position(300, 300);
}

void MainMenu::render_texture(){
	main_menu_background.render(0,0);
//	for( auto &current_queue : queue){
//		sprite_sheets[current_queue.sprite_num].render(current_queue.x, current_queue.y, current_queue.clip_num);
//	}
	test_text.render( 300, 300 );
//	_test_button.draw_element();
	queue.clear();
}

void MainMenu::update_logic(){
	if (input_data_->key_pressed[KEY_PRESS_W]){
		create_queue( &queue, 0, 0, 0, 0 );
	}
	if (input_data_->key_pressed[KEY_PRESS_A]){
		create_queue( &queue, 0, 0, 0, 1);
	}
	if (input_data_->key_pressed[KEY_PRESS_S]){
		create_queue( &queue, 0, 0, 0, 2);
	}
	if (input_data_->key_pressed[KEY_PRESS_D]){
		create_queue( &queue, 0, 0, 0, 3);
	}
	if (input_data_->key_pressed[KEY_PRESS_DEFAULT]){

	}
}

