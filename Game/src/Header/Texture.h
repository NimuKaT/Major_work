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
//	void init( SDL_Renderer* , std::string = std::string(), std::vector< SDL_Rect > = std::vector< SDL_Rect >() );
	void render(int, int);
	void set_as_render_target();
	SDL_Rect get_rect(int);
	void create_blank_texture(int, int);
	void set_renderer( SDL_Renderer* );
	void set_texture_alpha( Uint8 );
	void set_scale(float);
	void setBlendMode( SDL_BlendMode );

	void set_image_path(std::string);
	SDL_Rect get_rect();


private:
	void load_texture();
	void clip_from_texture();
	bool _is_renderable();

	std::string image_path;

protected:
	SDL_Texture* objectTexture;
	SDL_Renderer* _renderer_ptr;
	int _width, _height;
	Uint8 _textureAlpha;
	float _scale_factor;
	SDL_BlendMode _blendMode;
	SDL_Rect source_rect;


};

class SpriteSheet : public Texture{
public:
	SpriteSheet();
	void init();
	void render(int, int, int, double = 0.0);
	void set_sprite_rects(std::vector<SDL_Rect> &new_sprite_rect);

private:
	bool _is_renderable();
	std::vector<SDL_Rect> sprite_rect;

};

#endif /* TEXTURE_H_ */
