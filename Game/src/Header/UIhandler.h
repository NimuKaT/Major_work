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
	bool init_element(SDL_Renderer* renderer_ptr, std::string text, SpriteSheet* element_decoration, int clip_number);
	void hide_element(bool hide);
	void set_position(int x, int y);
	void draw_element();
	void set_padding( int padding_both = 0 );
	void set_padding( int padding_x = 0, int padding_y = 0 );
	void set_listner(Input_event* event_log);
	void set_event_trigger(bool* event_trigger);
	void update_event();
	void update_element(int mouse_x, int mouse_y, bool mouse_down);
	bool element_clicked();

protected:
	bool is_hidden_;
	SDL_Renderer* renderer_ptr_;
	Texture element_texture_;
	Text text_texture_;
	SpriteSheet* decoration_ptr_;
	std::string element_text_;
	int clip_number_;
	int x_position_, y_position_;
	int width_, height_;
	int padding_both_;
	int padding_x_, padding_y_;
	int* mouse_x_;
	int* mouse_y_;
	bool* mouse_MB1_state_;
	bool is_clicked_;
	bool* trigger_flag_;
	bool is_over_;
	bool has_released_over;
	bool click_started_on;
	bool unique_click;
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
