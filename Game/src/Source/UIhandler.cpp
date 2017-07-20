/*
 * UIhandler.cpp
 *
 *  Created on: 24Jan.,2017
 *      Author: ImuKaT
 */

#include "../Header/UIhandler.h"

//	class UI_element
//TODO make UI_element the base class with child classed of button, box, and slider bars

UI_element::UI_element(){
	is_hidden_ = false;
	renderer_ptr_ = NULL;
	decoration_ptr_ = NULL;
	clip_number_ = 0;
	x_position_ = 0;
	y_position_ = 0;
	width_ = 0;
	height_ = 0;
	padding_both_ = 0;
	padding_x_ = 0;
	padding_y_ = 0;
	mouse_x_ = NULL;
	mouse_y_ = NULL;
	mouse_MB1_state_ = NULL;
	is_clicked_ = false;
	trigger_flag_ = NULL;
	is_over_ = false;
	has_released_over = false;
	click_started_on = false;
	unique_click = true;
}

//TODO make text, element_decoration and clip_number independent of init_element
bool UI_element::init_element(SDL_Renderer* renderer_ptr, std::string text, SpriteSheet* element_decoration, int clip_number){
	bool element_init = false;
	renderer_ptr_ = renderer_ptr;
	decoration_ptr_ = element_decoration;
	element_text_ = text;
	clip_number_ = clip_number;
	SDL_Rect decoration_clip = decoration_ptr_->get_rect(clip_number_);

	if (decoration_clip.w == 0 || decoration_clip.h == 0){
		std::cout << "The clip number specified did not exist.\n" << std::endl;
	}
	else{
		width_ = decoration_clip.w;
		height_ = decoration_clip.h;
		element_texture_.set_renderer(renderer_ptr_);
		element_texture_.create_blank_texture(decoration_clip.w, decoration_clip.h);

		text_texture_.set_renderer(renderer_ptr_);
		text_texture_.set_font("Sans");
		text_texture_.set_text(text);
		text_texture_.set_color(255, 0, 0, 100);
		text_texture_.set_font_size(42);
		SDL_Point text_size = text_texture_.get_size();

		element_texture_.set_as_render_target();
		decoration_ptr_->render(0, 0, clip_number_);
		text_texture_.render((decoration_clip.w/2) - (text_size.x/2), (decoration_clip.h/2) - (text_size.y/2));
		element_init = true;
	}
	SDL_SetRenderTarget(renderer_ptr_, NULL);
	return element_init;
}

void UI_element::hide_element(bool hide){
	is_hidden_ = hide;
}

void UI_element::set_position(int x, int y){
	if (x >= 0){
		x_position_ = x;
	}
	if (y >= 0){
		y_position_ = y;
	}
}

void UI_element::draw_element(){
	if (!is_hidden_){
		element_texture_.render(x_position_, y_position_);
	}
}

void UI_element::set_padding(int padding_both){
	if(padding_both > 0 && padding_both < width_ / 2 && padding_both < height_ / 2){
		padding_both_ = padding_both;
	}
}

void UI_element::set_padding(int padding_x, int padding_y){
	if (padding_x > 0 && padding_x < width_ / 2){
		padding_x_ = padding_x;
		padding_both_ = 0;
	}
	if (padding_y > 0 && padding_y < width_ / 2){
		padding_y_ = padding_y;
		padding_both_ = 0;
	}
}

void UI_element::set_listner(Input_event* event_log){
	mouse_x_ = &event_log->mouse_x;
	mouse_y_ = &event_log->mouse_y;
	mouse_MB1_state_ = &event_log->key_pressed[KEY_PRESS_MB_1];
}

void UI_element::set_event_trigger(bool* event_triger){
	trigger_flag_ = event_triger;
}
// TODO remove pointer
void UI_element::update_event(){

	if (is_clicked_ && is_over_ && !*mouse_MB1_state_){
		*trigger_flag_ = true;
	}
	else if (is_over_ && *mouse_MB1_state_){
		is_clicked_ = true;
	}
	if (!*mouse_MB1_state_){
		is_clicked_ = false;
	}
}

void UI_element::update_element(int mouse_x, int mouse_y, bool mouse_down){
	if (!is_hidden_){
		if (x_position_ < mouse_x && x_position_ + width_ > mouse_x){
			if (y_position_ < mouse_y && y_position_ + height_ > mouse_y){
				is_over_ = true;
			}
			else{
				is_over_ = false;
			}
		}
		else{
			is_over_ = false;
		}

	//	Check if the button was clicked and released on element
		if (is_clicked_){
			if (is_over_ && !mouse_down && click_started_on){
				has_released_over = true;
			}
		}

	//	Checks click began on element
		if (is_over_ && mouse_down && unique_click){
			has_released_over = false;
			is_clicked_ = true;
			click_started_on = true;
		}
		else if(!is_over_ && mouse_down){
			click_started_on = false;
		}


	//	Check its a unique click
		if (mouse_down){
			unique_click = false;
		}
		else if (!mouse_down){
			unique_click = true;
			is_clicked_ = false;
		}
	}
	else{
		unique_click = true;
		is_clicked_ = false;
		has_released_over = false;
		click_started_on = false;
	}
}

bool UI_element::element_clicked(){
	bool has_clicked = has_released_over;
	has_released_over = false;
	return has_clicked;
}
