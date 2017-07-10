/*
 * Text.h
 *
 *  Created on: 27Jan.,2017
 *      Author: ImuKaT
 */

#ifndef TEXT_H_
#define TEXT_H_

#include "global.h"
#include "Texture.h"

class Text : public Texture{
public:
	Text();
	void init(SDL_Renderer* renderer_ptr, std::string font, std::string text, SDL_Rect rect);
	void render(int x, int y);
	void set_color(Uint8 red, Uint8 green, Uint8 blue, Uint8 alpha);
	bool set_font(std::string font);
	void set_font_size(Uint8 font_size);
	void set_space_size(int width, int height);
	void set_text(std::string text);
	void update_font();
	void set_alpha(Uint8 alpha);

private:
	std::string font_path_;
	std::string text_;
	TTF_Font* font_;
	SDL_Color color_;
	int font_size_;

	bool _is_renderable();
};

#endif /* TEXT_H_ */
