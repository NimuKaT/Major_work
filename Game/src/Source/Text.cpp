/*
 * Text.cpp
 *
 *  Created on: 27Jan.,2017
 *      Author: ImuKaT
 */

#include "../Header/Text.h"

/* global initilisation of available fonts */
const std::string SANS  = "Assets\\Fonts\\OpenSans-Regular.ttf";

Text::Text(){
	font_size_ = 0;
	font_ = NULL;
	set_color(0x00, 0x00, 0x00, 0x00);
}

void Text::init(SDL_Renderer* renderer_ptr, std::string font, std::string text, SDL_Rect rect){
	renderer_ptr_= renderer_ptr;
	source_rect_ = rect;
	width_ = rect.w;
	height_ = rect.h;
	text_ = text;

	set_font(font);
	update_font();
	create_blank_texture(width_, height_);
}

void Text::render(int x, int y){
	if (_is_renderable()){
		SDL_Surface* loaded_surface = TTF_RenderText_Solid(font_, text_.c_str(), color_);

		if (loaded_surface == NULL){
			printf("Unable to load image. TTF_Error: %s\n", TTF_GetError());
		}
		else{
			object_texture_ = SDL_CreateTextureFromSurface(renderer_ptr_, loaded_surface);

			if (object_texture_ == NULL){
				printf("Unable to create texture from surface. SDL Error: %s\n", SDL_GetError());
			}
			SDL_FreeSurface(loaded_surface);
		}
		TTF_SizeText(font_, text_.c_str(), &width_, &height_);
		SDL_Rect dstrect = {x, y, width_, height_};
		SDL_RenderCopy(renderer_ptr_, object_texture_, NULL, &dstrect);
	}
}

void Text::set_color(Uint8 red, Uint8 green, Uint8 blue , Uint8 alpha){
	if (red >= 0x00 && red <= 0xff){
		color_.r = red;
	}
	if (green >= 0x00 && green <= 0xff){
		color_.g = green;
	}
	if (blue >= 0x00 && blue <= 0xff){
		color_.b = blue;
	}
	if (alpha >= 0x00 && alpha <= 0xff){
		color_.a = alpha;
	}
}

void Text::set_alpha(Uint8 alpha){
	if (alpha >= 0x00 && alpha <= 0xff){
		color_.a = alpha;
	}
}

void Text::set_font_size(Uint8 font_size){
	if (font_size >= 0 && font_size <= 0xff && font_size != font_size_){
		font_size_ = font_size;
		update_font();
	}
}

bool Text::set_font(std::string font){
	bool font_switched = false;

	if (font == "Sans"){
		font_path_ = SANS;
		font_switched = true;
	}

	if (font_switched){
		update_font();
	}
	return font_switched;
}

void Text::set_space_size(int width, int height){
	if (width < 0 && width != width_){
		width_ = width;
	}
	if (height < 0 && height != height_){
		height_ = height;
	}
	create_blank_texture(width_, height_);
}

void Text::update_font(){
	TTF_CloseFont(font_); //Free currently open font
	font_ = TTF_OpenFont(font_path_.c_str(), font_size_);
}

void Text::set_text(std::string text){
	text_ = text;
}

bool Text::_is_renderable(){
	bool renderable = false;

	if (text_ != std::string()){
		if (font_path_ != std::string()){
			if (font_size_ > 0){
				if (width_ > 0 && height_ > 0){
					renderable = true;
				}
				else{
					std::cout<<"Could not render text. Texture width or height is 0.\n"<<std::endl;
				}
			}
			else{
				std::cout<<"Could not render text. Font size is 0.\n"<<std::endl;
			}
		}
		else{
			std::cout<<"Could not render text. Font path does not exist.\n"<<std::endl;
		}
	}
	else{
		std::cout<<"Could not render text. Text is empty.\n"<<std::endl;
	}
	return renderable;
}








