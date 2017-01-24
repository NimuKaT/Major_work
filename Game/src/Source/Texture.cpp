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
	if(!clips.empty()){
		sprite_clips.swap(clips);
	}
	else{
		std::cout << "clips are empty" << std::endl;
	}

	loadTexture();
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

		if( loadedSurface == NULL ){
			printf( "Unable to create texture from surface. SDL Error: %s\n", SDL_GetError() );
		}

		SDL_FreeSurface(loadedSurface);
		std::cout << "completed loading : " << image_path << std::endl;

	}
}

void Texture::render( int clip_num ){
//	std::cout << "rendering : "<< image_path << std::endl;
	if (!sprite_clips.empty()){
		SDL_Rect b = { 0, 0, sprite_clips[clip_num].w, sprite_clips[clip_num].h };
		SDL_RenderCopy(_renderer_ptr, objectTexture, &sprite_clips[clip_num], &b);
	}
	else{
		SDL_Rect c = { 0, 0, 1366, 720 };
		SDL_RenderCopy(_renderer_ptr, objectTexture, NULL, &c);
	}

}
