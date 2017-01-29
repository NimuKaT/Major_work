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
	void init(SDL_Renderer*, std::string, std::string, SDL_Rect);
	void render( int, int );
	void set_color( Uint8 = -1, Uint8 = -1, Uint8 = -1 , Uint8 = -1 );
	bool set_font(std::string);
	void set_font_size(int);
	void set_space_size( int, int );
	void update_font();

private:
	std::string _font_path;
	std::string _text;
	TTF_Font* _font;
	SDL_Color _color;
	int _font_size;
	SDL_Rect _srcrect;
};

#endif /* TEXT_H_ */