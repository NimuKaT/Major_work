/*
 * UIhandler.cpp
 *
 *  Created on: 24Jan.,2017
 *      Author: ImuKaT
 */

#include "../Header/UIhandler.h"

//	class UI_handler

bool UI_handler::init_UI(int w, int h, SDL_Renderer* target_renderer){
	bool UI_init_flag = false;

	_renderer_ptr = target_renderer;

	//TODO stub

	return UI_init_flag;
};

void UI_handler::add_element(std::string text, Texture* element_decoration, int clip_number){


};

Texture* UI_handler::get_UI_texture(){
	return &UI_base_texture;
};


//	class UI_element

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
		_element_texture.create_blank_texture( decoration_clip.w, decoration_clip.h );
		_element_texture.set_as_render_target();
		_decoration_ptr->render(_clip_number);

		element_init = true;

	}
	SDL_SetRenderTarget( _renderer_ptr, NULL);

	return element_init;

};
