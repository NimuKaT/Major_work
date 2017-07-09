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
	bool init_element(SDL_Renderer*, std::string, SpriteSheet*, int);
	void hide_element(bool);
	void set_position( int, int );
	bool is_over_element( int, int );
	void draw_element();
	void set_padding( int = 0 );
	void set_padding( int = 0, int = 0 );
	void set_listner(Input_event*);
	void set_event_trigger(bool*);
	void update_event();

protected:
	bool is_hidden;
	SDL_Renderer* _renderer_ptr;
	Texture _element_texture;
	Text _text_texture;
	SpriteSheet* _decoration_ptr;
	std::string _element_text;
	int _clip_number;
	int _x_position, _y_position;
	int _width, _height;
	int _padding_both;
	int _padding_x, _padding_y;
	int* mouse_x_;
	int* mouse_y_;
	bool* mouse_MB1_state_;
	bool is_clicked_;
	bool* trigger_flag_;
	bool is_over_;
};

class UI_button : public UI_element{

};

class UI_box : public UI_element{

};

class UI_slider_bar : public UI_element{

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
