/*
 * Texture.cpp
 *
 *  Created on: 15Jan.,2017
 *      Author: ImuKaT
 */

#include "../Header/Texture.h"

void add_rect_to_vector(std::vector<SDL_Rect> &rect_vector, int x, int y, int h, int w){
	SDL_Rect temp_rect;
	temp_rect.x = x;
	temp_rect.y = y;
	temp_rect.h = h;
	temp_rect.w = w;
	rect_vector.push_back(temp_rect);
};

void Texture::init(SDL_Renderer* targetRenderer, std::string path, std::vector<SDL_Rect> clips) {
	_renderer_ptr= targetRenderer;
	image_path = path;
	loadTexture();
	if(!clips.empty()){
		sprite_clips.swap(clips);
	}
	else{
		clip_from_texture();
		std::cout << "clips are empty\n" << _width << "\n" << _height <<std::endl;
	}


};

void Texture::loadTexture(){

	//Output as final texture
	objectTexture = NULL;

	//Load image from specified path
	SDL_Surface* loadedSurface = IMG_Load( image_path.c_str() );

	if( loadedSurface == NULL ){
		printf( "Unable to load image. SDL_image Error: %s\n", IMG_GetError() );
	}
	else{
		objectTexture = SDL_CreateTextureFromSurface( _renderer_ptr, loadedSurface );

		if( objectTexture == NULL ){
			printf( "Unable to create texture from surface. SDL Error: %s\n", SDL_GetError() );
		}

		SDL_FreeSurface(loadedSurface);
		std::cout << "completed loading : " << image_path << std::endl;

	}
}

void Texture::render( int x, int y, int clip_num ){
//	std::cout << "rendering : "<< image_path << std::endl;
	if (!sprite_clips.empty()){
		SDL_Rect dstrect = { x, y, sprite_clips[clip_num].w, sprite_clips[clip_num].h };
		SDL_RenderCopy(_renderer_ptr, objectTexture, &sprite_clips[clip_num], &dstrect );
	}

}

void Texture::set_as_render_target(){

	//makes the target of render this texture
	SDL_SetRenderTarget( _renderer_ptr, objectTexture );
}

void Texture::create_blank_texture(int width, int height){
	objectTexture = SDL_CreateTexture( _renderer_ptr, SDL_PIXELFORMAT_RGBA8888, NULL, width, height);
	if( objectTexture == NULL){
		std::cout << "Could not create blank texture. SDL_Error: %s\n" << SDL_GetError() << std::endl;
	}
	else{
		clip_from_texture();
	}
}

SDL_Rect Texture::get_rect(int clip_number){
	return sprite_clips[clip_number];
}

void Texture::clip_from_texture(){
	SDL_QueryTexture(objectTexture, NULL, NULL, &_width, &_height);
	sprite_clips.clear();
	add_rect_to_vector(sprite_clips, 0, 0, _height, _width);
}



