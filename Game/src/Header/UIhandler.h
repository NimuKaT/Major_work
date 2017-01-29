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

class UI_element{
public:
	bool init_element(SDL_Renderer*, std::string, Texture*, int);

private:
	bool is_hidden;
	SDL_Renderer* _renderer_ptr;
	Texture _element_texture;
	Texture* _decoration_ptr;
	std::string _element_text;
	int _clip_number;

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
