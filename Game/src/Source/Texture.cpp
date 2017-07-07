/*
 * Texture.cpp
 *
 *  Created on: 15Jan.,2017
 *      Author: ImuKaT
 */

#include "../Header/Texture.h"

#define MIN_FACTOR 0.1f
#define MAX_FACTOR 8.0f

//TODO move somewhere else or change stuff
void add_rect_to_vector(std::vector<SDL_Rect> &rect_vector, int x, int y, int h, int w){
	SDL_Rect temp_rect;
	temp_rect.x = x;
	temp_rect.y = y;
	temp_rect.h = h;
	temp_rect.w = w;
	rect_vector.push_back(temp_rect);
};

Texture::Texture(){
	objectTexture = NULL;
	_renderer_ptr = NULL;
	_width = 0;
	_height = 0;
	_textureAlpha = 255;
	_scale_factor = 1.0;
	_blendMode = SDL_BLENDMODE_ADD;
}

//void Texture::init(SDL_Renderer* targetRenderer, std::string path, std::vector<SDL_Rect> clips) {
//	_renderer_ptr= targetRenderer;
//	image_path = path;
//	if( path != std::string() ){
//		load_texture();
//		if(!clips.empty()){
//			sprite_clips.swap(clips);
//		}
//		else{
//			clip_from_texture();
////			std::cout << "clips are empty\n" << _width << "\n" << _height <<std::endl;	logPoint
//		}
//	}
//	else{
//		create_blank_texture( 100, 100);
//	}
//
//
//};

void Texture::load_texture(){

	//Output as final texture
	objectTexture = NULL;

	//Load image from specified path
	SDL_Surface* loadedSurface = IMG_Load( image_path.c_str() );

	if( loadedSurface == NULL ){
		printf( "Unable to load image. SDL_image Error: %s\n%s\n", IMG_GetError(), image_path.c_str());
	}
	else{
		objectTexture = SDL_CreateTextureFromSurface( _renderer_ptr, loadedSurface );

		if( objectTexture == NULL ){
			printf( "Unable to create texture from surface. SDL Error: %s\n", SDL_GetError() );
		}

		SDL_FreeSurface(loadedSurface);
		setBlendMode(SDL_BLENDMODE_BLEND);
//		std::cout << "completed loading : " << image_path << std::endl;	logPoint

	}
}

void Texture::render( int x, int y){
//	std::cout << "rendering : "<< image_path << std::endl; logPoint
	if ( _is_renderable() ){
		SDL_SetRenderDrawBlendMode( _renderer_ptr, _blendMode );
		SDL_Rect dstrect = { x, y, floor( source_rect.w * _scale_factor ), floor( source_rect.h * _scale_factor ) };
		SDL_RenderCopy(_renderer_ptr, objectTexture, &source_rect, &dstrect );
	}

}

void Texture::set_as_render_target(){
	//makes the target of render this texture
	SDL_SetRenderTarget( _renderer_ptr, objectTexture );
}

void Texture::create_blank_texture(int width, int height){

	SDL_SetRenderDrawBlendMode(_renderer_ptr, SDL_BLENDMODE_BLEND);
	SDL_SetTextureBlendMode(objectTexture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderDrawColor( _renderer_ptr, 0xFF, 0xFF, 0xFF, 0x00 );
	objectTexture = SDL_CreateTexture( _renderer_ptr, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, width, height);
	setBlendMode(SDL_BLENDMODE_BLEND);

	if( objectTexture == NULL){
		std::cout << "Could not create blank texture. SDL_Error: %s\n" << SDL_GetError() << std::endl;
	}
	else{
		clip_from_texture();
	}
}

//SDL_Rect Texture::get_rect(int clip_number){
////	return sprite_clips[clip_number];
//}

void Texture::clip_from_texture(){
	SDL_QueryTexture(objectTexture, NULL, NULL, &_width, &_height);
	source_rect.x = 0;
	source_rect.y = 0;
	source_rect.w = _width;
	source_rect.h = _height;

}

void Texture::set_renderer(	SDL_Renderer* targetRenderer ){
	_renderer_ptr = targetRenderer;
}

bool Texture::_is_renderable(){
	bool renderable = false;
	if( _renderer_ptr != NULL ){
		if( objectTexture != NULL ){
			if(source_rect.w == 0 || source_rect.h == 0){
				renderable = true;
			}
			else{
				std::cout << "Could not render image. Clips are missing.\n" << std::endl;
			}
		}
		else{
			std::cout << "Could not render image. Texture has not been loaded.\n" << std::endl;

		}
	}
	else{
		std::cout << "Could not render image. Renderer pointer has not been passed.\n" << std::endl;
	}

	return renderable;
}

void Texture::set_texture_alpha( Uint8 alpha ){
	SDL_SetTextureAlphaMod( objectTexture, alpha);
	_textureAlpha = alpha;

}

void Texture::set_scale( float factor ){
	if ( factor > MIN_FACTOR && factor < MAX_FACTOR ){
		_scale_factor = factor;
	}
}

void Texture::setBlendMode( SDL_BlendMode mode ){
	SDL_SetTextureBlendMode( objectTexture, mode );
	_blendMode = mode;
}

void Texture::set_image_path(std::string path){
	image_path = path;
	load_texture();
	clip_from_texture();
}

SDL_Rect Texture::get_rect(){
	return source_rect;
}

SpriteSheet::SpriteSheet(){

}

void SpriteSheet::render(int x, int y, int sprite_num, double angle){
	if(_is_renderable()){
		SDL_Rect destination_rect = {x, y, source_rect.w, source_rect.h};
		SDL_RenderCopy(_renderer_ptr, objectTexture, &sprite_rect[sprite_num], &destination_rect);
	}
}

void SpriteSheet::set_sprite_rects(std::vector<SDL_Rect> &new_sprite_rect){
	sprite_rect = new_sprite_rect;
}


bool SpriteSheet::_is_renderable(){
	bool renderable = false;

	if( _renderer_ptr != NULL ){
		if( objectTexture != NULL ){
			if(!sprite_rect.empty()){
				renderable = true;
			}
			else{
				std::cout << "Could not render image. Clips are missing.\n" << std::endl;
			}
		}
		else{
			std::cout << "Could not render image. Texture has not been loaded.\n" << std::endl;

		}
	}
	else{
		std::cout << "Could not render image. Renderer pointer has not been passed.\n" << std::endl;
	}

	return renderable;
}





















