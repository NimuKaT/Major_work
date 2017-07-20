/*
 * GameMenu.cpp
 *
 *  Created on: 2017/02/22
 *      Author: Imukat
 */

#include "../Header/GameMenu.h"

GameMenu::GameMenu(SDL_Renderer* renderer_ptr, std::shared_ptr<Input_event> &input_ptr) {
	current_menu = GAME_MENU;
	next_menu = current_menu;

	is_paused = false;
	unique_press = true;
	quit_pressed = false;
	quit = false;
	input_data_ = input_ptr;
	renderer_ptr_ = renderer_ptr;

	button_deco.set_renderer(renderer_ptr_);
	button_deco.set_image_path(IMAGE_PATHS[TEST_UI_ELEMENT]);
	button_deco.set_sprite_rects(IMAGE_RECTS[TEST_UI_ELEMENT]);

	pause_menu_shade_.set_renderer(renderer_ptr_);
	pause_menu_shade_.create_blank_texture(3840, 2160, 0x00, 0x00, 0x00, 0xFF);
	pause_menu_shade_.set_texture_alpha(0xA0);

	paused_text.set_renderer(renderer_ptr_);
	paused_text.set_text("Paused");
	paused_text.set_color(0xFF, 0xFF, 0xFF, 0xFF);
	paused_text.set_font("Sans");
	paused_text.set_font_size(240);

	quit_confirmation_text_.set_renderer(renderer_ptr_);
	quit_confirmation_text_.set_text("Are you sure?");
	quit_confirmation_text_.set_color(0xFF, 0xFF, 0xFF, 0xFF);
	quit_confirmation_text_.set_font("Sans");
	quit_confirmation_text_.set_font_size(240);

	resume_button.init_element(renderer_ptr_, "Resume", &button_deco, 0);
	resume_button.hide_element(true);
	resume_button.set_position(1595,1120);

	quit_button.init_element(renderer_ptr_, "Quit", &button_deco, 0);
	quit_button.hide_element(true);
	quit_button.set_position(1920-325,1320);

	quit_no_button_.init_element(renderer_ptr_, "No", &button_deco, 0);
	quit_no_button_.hide_element(true);
	quit_no_button_.set_position(2000,1320);

	quit_yes_button_.init_element(renderer_ptr_, "Yes", &button_deco, 0);
	quit_yes_button_.hide_element(true);
	quit_yes_button_.set_position(1190,1320);
}

void GameMenu::update_logic(){
	if (!game_instance){
		game_instance = std::unique_ptr<Engine>(new Engine());
		game_instance->get_data(renderer_ptr_);
		game_instance->load_stage(STAGE_TEST);
	}
	if (!input_data_.expired()){
		if (input_data_.lock()->key_pressed[KEY_PRESS_ESC]){
			if (unique_press == true){
				if (!is_paused){
					is_paused = true;
				}
				else{
					is_paused = false;
				}
				resume_button.hide_element(!is_paused);
				quit_button.hide_element(!is_paused);
				unique_press = false;
				quit_pressed = false;
			}
		}
		else{
			unique_press = true;
		}
		if (input_data_.lock()->key_pressed[KEY_PRESS_SPACE] && game_instance->is_game_end()){
			game_instance = std::unique_ptr<Engine>(new Engine());
			game_instance->get_data(renderer_ptr_);
			game_instance->load_stage(STAGE_TEST);
		}

		if (!is_paused){
			if(!input_data_.expired()){
				game_instance->main_loop(input_data_);
			}
		}
		else if(is_paused){
			if (!quit_pressed){
				if(!input_data_.expired()){
					resume_button.update_element(input_data_.lock()->mouse_x, input_data_.lock()->mouse_y, input_data_.lock()->key_pressed[KEY_PRESS_MB_1]);
					quit_button.update_element(input_data_.lock()->mouse_x, input_data_.lock()->mouse_y, input_data_.lock()->key_pressed[KEY_PRESS_MB_1]);
					if (resume_button.element_clicked()){
						is_paused = false;
					}
					if (quit_button.element_clicked()){
						quit_pressed = true;
					}
				}
			}
			else if (quit_pressed){
				if(!input_data_.expired()){
					quit_no_button_.update_element(input_data_.lock()->mouse_x, input_data_.lock()->mouse_y, input_data_.lock()->key_pressed[KEY_PRESS_MB_1]);
					quit_yes_button_.update_element(input_data_.lock()->mouse_x, input_data_.lock()->mouse_y, input_data_.lock()->key_pressed[KEY_PRESS_MB_1]);
					if (quit_no_button_.element_clicked()){
						quit_pressed = false;
					}
					if (quit_yes_button_.element_clicked()){
						game_instance.release();
						is_paused = false;
						quit_pressed = false;
						next_menu = MAIN_MENU;
					}
				}
			}
			resume_button.hide_element(quit_pressed);
			quit_button.hide_element(quit_pressed);
			quit_no_button_.hide_element(!quit_pressed);
			quit_yes_button_.hide_element(!quit_pressed);
		}
	}
}


void GameMenu::render_texture(){
	std::shared_ptr<Texture> current_game_frame;
	if (game_instance){
		current_game_frame = game_instance->get_last_texture();
		current_game_frame->render(0,0);
	}
	if (is_paused){
		pause_menu_shade_.render(0,0);
		if (!quit_pressed){
			paused_text.render(1920 - paused_text.get_size().x/2, 1080 - paused_text.get_size().y/2 - 400);
			resume_button.draw_element();
			quit_button.draw_element();
		}
		else if (quit_pressed){
			quit_confirmation_text_.render(1920 - quit_confirmation_text_.get_size().x/2, 1080 - quit_confirmation_text_.get_size().y/2 - 400);
			quit_no_button_.draw_element();
			quit_yes_button_.draw_element();
		}
	}
}
