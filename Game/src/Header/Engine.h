/*
 * Engine.h
 *
 *  Created on: 2017/03/08
 *      Author: Imukat
 */

#ifndef ENGINE_H_
#define ENGINE_H_

#include "Global.h"
#include "Object.h"

//stub constants

const int TILE_DIMENSION = 16;


// Space for enums for stages enemy types etc.





class Engine {
public:
	Engine();
	~Engine();
	bool load_stage( Uint8 );
	void main_loop();

private:
	bool stage_loaded;
	Uint8 stage_id;
	std::vector < std::shared_ptr < Object > > object_list;
	std::shared_ptr < Player > player_object;


};

#endif /* ENGINE_H_ */
