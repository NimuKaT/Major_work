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


void add_rect_to_vector(std::vector<SDL_Rect> &, int, int, int, int);

class Texture{
public:
	Texture();
	void render(int x, int y);
	void set_as_render_target();
	SDL_Rect get_rect();
	void create_blank_texture(int width, int height, Uint8 red = 0x00, Uint8 green = 0x00, Uint8 blue = 0x00, Uint8 alpha = 0x00);
	void set_renderer(SDL_Renderer* renderer_ptr);
	void set_texture_alpha(Uint8 alpha);
	void setBlendMode(SDL_BlendMode mode);

	void set_image_path(std::string path);


private:
	void load_texture();
	void clip_from_texture();
	bool _is_renderable();

	std::string image_path_;

protected:
	SDL_Texture* object_texture_;
	SDL_Renderer* renderer_ptr_;
	int width_, height_;
	Uint8 texture_alpha_;
	SDL_BlendMode blend_mode_;
	SDL_Rect source_rect_;


};

class SpriteSheet : public Texture{
public:
	SpriteSheet();
	void init();
	void render(int x, int y, int sprite_num, double angle = 0.0);
	void set_sprite_rects(std::vector<SDL_Rect> &sprite_rect);
	SDL_Rect get_rect(Uint8 rect_num);

private:
	bool _is_renderable();
	std::vector<SDL_Rect> sprite_rect_;

};

#endif /* TEXTURE_H_ */
