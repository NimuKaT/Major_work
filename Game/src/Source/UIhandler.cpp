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
	is_hidden = false;
	_renderer_ptr = NULL;
	_decoration_ptr = NULL;
	_clip_number = 0;
	_x_position = 0;
	_y_position = 0;
	_width = 0;
	_height = 0;
	_padding_both = 0;
	_padding_x = 0;
	_padding_y = 0;
}

//TODO make text, element_decoration and clip_number independent of init_element
bool UI_element::init_element(SDL_Renderer* target_renderer, std::string text, Texture* element_decoration, int clip_number){

	bool element_init = false;

	_renderer_ptr = target_renderer;
	_decoration_ptr = element_decoration;
	_element_text = text;
	_clip_number = clip_number;
	SDL_Rect decoration_clip = _decoration_ptr->get_rect(_clip_number);
	if( decoration_clip.w == 0 || decoration_clip.h == 0 ){
		std::cout << "The clip number specified did not exist.\n" << std::endl;
	}
	else{
		_element_texture.get_renderer( _renderer_ptr );
		_element_texture.create_blank_texture( decoration_clip.w, decoration_clip.h );

		SDL_Rect text_clip = { 0, 0, decoration_clip.w - 2*_padding_both, decoration_clip.h - 2*_padding_both};

		_text_texture.init( _renderer_ptr, "Sans", text, text_clip);
		_text_texture.set_color( 255, 0, 0, 100);
		_text_texture.set_font_size( 42 );

		_element_texture.set_as_render_target();

		_decoration_ptr->render( 0 ,0, _clip_number);
		_text_texture.render( 5, 5 );



		element_init = true;

	}
	SDL_SetRenderTarget( _renderer_ptr, NULL);

	return element_init;

};

void UI_element::hide_element(bool hide){
	is_hidden = hide;
}

void UI_element::set_position( int x, int y ){
	if( x >= 0){
		_x_position = x;
	}
	if( y >= 0){
		_y_position = y;
	}
}

bool UI_element::is_over_element( int x_mouse, int y_mouse ){
	bool is_over = false;

	return is_over;
}

void UI_element::draw_element(){
	if( !is_hidden){
		_element_texture.render(_x_position, _y_position, 0);
	}
}

void UI_element::set_padding(int padding_size){
	if( padding_size > 0 && padding_size < _width / 2 && padding_size < _height / 2 ){
		_padding_both = padding_size;
	}
}

void UI_element::set_padding(int padding_x, int padding_y){
	if( padding_x > 0 && padding_x < _width / 2 ){
		_padding_x = padding_x;
		_padding_both = 0;
	}
	if( padding_y > 0 && padding_y < _width / 2 ){
		_padding_y = padding_y;
		_padding_both = 0;
	}
}






