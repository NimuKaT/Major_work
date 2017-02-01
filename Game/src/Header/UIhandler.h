/*
 * UIhandler.h
 *
 *  Created on: 24Jan.,2017
 *      Author: ImuKaT
 */

#ifndef UIHANDLER_H_
#define UIHANDLER_H_

#include "Global.h"


#include "Texture.h"
#include "Text.h"

class UI_element{
public:
	UI_element();
	bool init_element(SDL_Renderer*, std::string, Texture*, int);
	void hide_element(bool);
	void set_position( int, int );
	bool is_over_element( int, int );
	void draw_element();

private:
	bool is_hidden;
	SDL_Renderer* _renderer_ptr;
	Texture _element_texture;
	Text _text_texture;
	Texture* _decoration_ptr;
	std::string _element_text;
	int _clip_number;
	int _x_position, _y_position;

};

class UI_handler{
public:
	bool init_UI(int, int, SDL_Renderer*);
	void add_element(std::string, Texture*, int); //functions that adds an widget to the interface
	Texture* get_UI_texture();

private:
	Texture UI_base_texture;
	std::vector<UI_element> elements;
	SDL_Renderer* _renderer_ptr;
};



#endif /* UIHANDLER_H_ */
