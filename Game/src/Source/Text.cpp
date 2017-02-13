/*
 * Text.cpp
 *
 *  Created on: 27Jan.,2017
 *      Author: ImuKaT
 */

#include "../Header/Text.h"

/* global initilisation of available fonts */
const std::string SANS  = "Assets/Fonts/OpenSans-Regular.ttf";

Text::Text(){
	_font_size = 0;
	_font = NULL;
	set_color( 0x00, 0x00, 0x00, 0x00 );
}

//TODO make font, text, clip intialised out of init
void Text::init(SDL_Renderer* target_renderer, std::string font, std::string text, SDL_Rect clip){
	_renderer_ptr= target_renderer;
	_srcrect = clip;
	_width = clip.w;
	_height = clip.h;
	_text = text;

	set_font(font);
	update_font();
	create_blank_texture( _width, _height );

}


void Text::render( int x, int y ){

	if( _is_renderable() ){

		SDL_Surface* loadedSurface = TTF_RenderText_Solid( _font, _text.c_str(), _color);

		if( loadedSurface == NULL ){
			printf( "Unable to load image. TTF_Error: %s\n", TTF_GetError() );
		}
		else{
			objectTexture = SDL_CreateTextureFromSurface( _renderer_ptr, loadedSurface );

			if( objectTexture == NULL ){
				printf( "Unable to create texture from surface. SDL Error: %s\n", SDL_GetError() );
			}

			SDL_FreeSurface(loadedSurface);
		}

		SDL_Rect dstrect = { x, y, _width, _height };

		SDL_RenderCopy(_renderer_ptr, objectTexture, &_srcrect, &dstrect);

	}
}

void Text::set_color( Uint8 r, Uint8 g, Uint8 b , Uint8 a){

	if( r >= 0x00 && r <= 0xff ){
		_color.r = r;
	}
	if( g >= 0x00 && g <= 0xff ){
		_color.g = g;
	}
	if( b >= 0x00 && b <= 0xff ){
		_color.b = b;
	}
	if( a >= 0x00 && a <= 0xff ){
		_color.a = a;
	}
}

void Text::set_alpha( Uint8 a ){
	if( a >= 0x00 && a <= 0xff ){
		_color.a = a;
	}
}

void Text::set_font_size( int size ){
	if(size >= 0 && size <= 255 && size != _font_size){
		_font_size = size;
		update_font();
	}
}

bool Text::set_font(std::string font){
	bool font_switched = false;


	if( font == "Sans" ){
		_font_path = SANS;
		font_switched = true;
	}

	if( font_switched ){
		update_font();
	}

	return font_switched;
}

void Text::set_space_size( int width, int height){

	if( width < 0 && width != _width){
		_width = width;
	}
	if( height < 0 && height != _height){
		_height = height;
	}

	create_blank_texture( _width, _height );

}

void Text::update_font(){
	TTF_CloseFont( _font ); //Free currently open font
	_font = TTF_OpenFont( _font_path.c_str(), _font_size);
}

void Text::set_text( std::string text){
	_text = text;
}

//TODO output statements when error occurs
bool Text::_is_renderable(){
	bool renderable = false;

	if( _text != std::string() ){
		if( _font_size > 0){
			renderable = true;
		}
	}
	return renderable;
}








