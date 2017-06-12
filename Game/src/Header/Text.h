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
	void set_color( Uint8, Uint8, Uint8 , Uint8 );
	bool set_font(std::string);
	void set_font_size(int);
	void set_space_size( int, int );
	void set_text( std::string );
	void update_font();
	void set_alpha( Uint8 );

private:
	std::string _font_path;
	std::string _text;
	TTF_Font* _font;
	SDL_Color _color;
	int _font_size;
	SDL_Rect _srcrect;

	bool _is_renderable();
};

#endif /* TEXT_H_ */
