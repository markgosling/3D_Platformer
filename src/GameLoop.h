#include <SDL2/SDL.h>
#include <memory>
#include "GameWorld.h"

/*
 * GameLoop.h
 *
 *  Created on: 23 Apr 2016
 *      Author: mark
 */

#ifndef SRC_GAMELOOP_H_
#define SRC_GAMELOOP_H_

class GameLoop{

public:
	std::shared_ptr<SDL_Window> InitWorld();
	void Draw(const std::shared_ptr<SDL_Window> &window, const std::shared_ptr<GameWorld> &game_world);
	void run();
};



#endif /* SRC_GAMELOOP_H_ */
