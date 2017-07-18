/*
 * AI.h
 *
 *  Created on: 17Jul.,2017
 *      Author: ImuKaT
 */

#ifndef AI_H_
#define AI_H_

#include "Global.h"
#include "Object.h"

class AI {
public:
	AI();
	virtual ~AI();
	virtual void get_next_movement(std::vector<std::shared_ptr<Wall>> &wall_objects,
			std::vector<std::shared_ptr<Player>> &player_objects,
			std::vector<std::shared_ptr<Bullet>> &player_bullets) = 0;
protected:

};

class GabBot : public AI{
public:
	GabBot();
	~GabBot();
	void get_next_movement(std::vector<std::shared_ptr<Wall>> &wall_objects,
			std::vector<std::shared_ptr<Player>> &player_objects,
			std::vector<std::shared_ptr<Bullet>> &player_bullets);
};

#endif /* AI_H_ */
