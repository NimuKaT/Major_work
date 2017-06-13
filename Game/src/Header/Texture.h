/*
 * Texture.h
 *
 *  Created on: 19Jan.,2017
 *      Author: ImuKaT
 */

#ifndef TEXTURE_H_
#define TEXTURE_H_

#include <fstream>

#include "Global.h"


void add_rect_to_vector(std::vector< SDL_Rect> &, int, int, int, int);

class Texture{
public:
	Texture();
	void init( SDL_Renderer* , std::string = std::string(), std::vector< SDL_Rect > = std::vector< SDL_Rect >() );
	void render(int = 0, int = 0, int = 0);
	void set_as_render_target();
	SDL_Rect get_rect(int);
	void create_blank_texture(int, int);
	void get_renderer( SDL_Renderer* );
	void set_texture_alpha( Uint8 );
	void set_scale(float);
	void setBlendMode( SDL_BlendMode );



private:
	void load_texture();
	void clip_from_texture();
	bool _is_renderable();

	std::string image_path;

protected:
	SDL_Texture* objectTexture;
	std::vector< SDL_Rect > sprite_clips;
	SDL_Renderer* _renderer_ptr;
	int _width, _height;
	Uint8 _textureAlpha;
	float _scale_factor;
	SDL_BlendMode _blendMode;


};



#endif /* TEXTURE_H_ */
