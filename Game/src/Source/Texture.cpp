/*
 * Texture.cpp
 *
 *  Created on: 15Jan.,2017
 *      Author: ImuKaT
 */

#include "../Header/Texture.h"

//TODO move somewhere else or change stuff
void add_rect_to_vector(std::vector<SDL_Rect> &rect_vector_ref, int x, int y, int h, int w){
	SDL_Rect temp_rect;
	temp_rect.x = x;
	temp_rect.y = y;
	temp_rect.h = h;
	temp_rect.w = w;
	rect_vector_ref.push_back(temp_rect);
};

Texture::Texture(){
	object_texture_ = NULL;
	renderer_ptr_ = NULL;
	width_ = 0;
	height_ = 0;
	texture_alpha_ = 255;
	blend_mode_ = SDL_BLENDMODE_ADD;
}

void Texture::load_texture(){
	//Output as final texture
	object_texture_ = NULL;

	//Load image from specified path
	SDL_Surface* loaded_surface = IMG_Load( image_path_.c_str() );

	if (loaded_surface == NULL){
		printf("Unable to load image. SDL_image Error: %s\n%s\n", IMG_GetError(), image_path_.c_str());
	}
	else{
		object_texture_ = SDL_CreateTextureFromSurface(renderer_ptr_, loaded_surface);

		if (object_texture_ == NULL){
			printf("Unable to create texture from surface. SDL Error: %s\n", SDL_GetError());
		}
		SDL_FreeSurface(loaded_surface);
		setBlendMode(SDL_BLENDMODE_BLEND);
	}
}

void Texture::render(int x, int y){
	if (_is_renderable()){
		SDL_SetRenderDrawBlendMode(renderer_ptr_, blend_mode_);
		SDL_Rect destination_rect = {x, y, source_rect_.w, source_rect_.h};
		SDL_RenderCopy(renderer_ptr_, object_texture_, &source_rect_, &destination_rect);
	}
}

void Texture::set_as_render_target(){
	//makes the target of render this texture
	SDL_SetRenderTarget(renderer_ptr_, object_texture_);
}

void Texture::create_blank_texture(int width, int height){
	SDL_SetRenderDrawBlendMode(renderer_ptr_, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(object_texture_, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor(renderer_ptr_, 0xFF, 0xFF, 0xFF, 0x00);
	object_texture_ = SDL_CreateTexture(renderer_ptr_, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	setBlendMode(SDL_BLENDMODE_BLEND);

	if (object_texture_ == NULL){
		std::cout << "Could not create blank texture. SDL_Error: %s\n" << SDL_GetError() << std::endl;
	}
	else{
		clip_from_texture();
	}
}

void Texture::clip_from_texture(){
	SDL_QueryTexture(object_texture_, NULL, NULL, &width_, &height_);
	source_rect_.x = 0;
	source_rect_.y = 0;
	source_rect_.w = width_;
	source_rect_.h = height_;
}

void Texture::set_renderer(SDL_Renderer* renderer_ptr ){
	renderer_ptr_ = renderer_ptr;
}

bool Texture::_is_renderable(){
	bool renderable = false;

	if(renderer_ptr_ != NULL){
		if(object_texture_ != NULL){
			if(!source_rect_.w == 0 || !source_rect_.h == 0){
				renderable = true;
			}
			else{
				std::cout<<"Could not render image. Clips are missing.\n"<<std::endl;
			}
		}
		else{
			std::cout<<"Could not render image. Texture has not been loaded.\n"<<std::endl;
		}
	}
	else{
		std::cout<<"Could not render image. Renderer pointer has not been passed.\n"<<std::endl;
	}
	return renderable;
}

void Texture::set_texture_alpha(Uint8 alpha){
	SDL_SetTextureAlphaMod(object_texture_, alpha);
	texture_alpha_ = alpha;
}

void Texture::setBlendMode(SDL_BlendMode mode){
	SDL_SetTextureBlendMode(object_texture_, mode);
	blend_mode_ = mode;
}

void Texture::set_image_path(std::string path){
	image_path_ = path;
	load_texture();
	clip_from_texture();
}

SDL_Rect Texture::get_rect(){
	return source_rect_;
}

SpriteSheet::SpriteSheet(){

}

void SpriteSheet::render(int x, int y, int sprite_num, double angle){
	if(_is_renderable()){
		SDL_SetRenderDrawBlendMode(renderer_ptr_, blend_mode_);
		SDL_Rect destination_rect = {x, y, source_rect_.w, source_rect_.h};
		SDL_RenderCopy(renderer_ptr_, object_texture_, &sprite_rect_[sprite_num], &destination_rect);
	}
}

void SpriteSheet::set_sprite_rects(std::vector<SDL_Rect> &sprite_rect){
	sprite_rect_ = sprite_rect;
}

bool SpriteSheet::_is_renderable(){
	bool renderable = false;

	if (renderer_ptr_ != NULL){
		if (object_texture_ != NULL){
			if (!sprite_rect_.empty()){
				renderable = true;
			}
			else{
				std::cout <<"Could not render image. Clips are missing.\n"<<std::endl;
			}
		}
		else{
			std::cout <<"Could not render image. Texture has not been loaded.\n"<<std::endl;
		}
	}
	else{
		std::cout<<"Could not render image. Renderer pointer has not been passed.\n"<<std::endl;
	}
	return renderable;
}

SDL_Rect SpriteSheet::get_rect(Uint8 rect_num){
	return sprite_rect_[rect_num];
}




















